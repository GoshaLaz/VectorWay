#include "vectorway/open_street_maps.h"
#include <curl/curl.h>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<OSMRoad> getRoadsFromOSM(double south, double west, double north, double east) {
    std::vector<OSMRoad> roads;

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL\n";
        return roads;
    }


    std::ostringstream query;
    query << "[out:json][timeout:25];"
      << "way[\"highway\"]("
      << south << "," << west << "," << north << "," << east << ");"
      << "out geom;";


    std::string postData = "data=" + query.str();

    std::string url = "https://overpass.kumi.systems/api/interpreter";
    std::string response;

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "User-Agent: VectorWay-Library/1.0");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << "\n";
        return roads;
    }

    if (http_code != 200) {
        std::cerr << "HTTP error: " << http_code << "\n";
        std::cerr << "Response: " << response.substr(0, 300) << "...\n";
        return roads;
    }

    try {
        json j = json::parse(response);

        if (!j.contains("elements")) {
            std::cerr << "Invalid JSON from Overpass API\n";
            return roads;
        }

        for (auto& elem : j["elements"]) {
            if (elem["type"] != "way") continue;

            OSMRoad r;
            r.id = std::to_string(elem.value("id", 0ULL));

            if (elem.contains("tags")) {
                r.name = elem["tags"].value("name", "");
                r.type = elem["tags"].value("highway", "");
            }

            if (elem.contains("geometry")) {
                for (auto& g : elem["geometry"]) {
                    double lat = g.value("lat", 0.0);
                    double lon = g.value("lon", 0.0);
                    r.coordinates.push_back({lat, lon});
                }
            }

            roads.push_back(r);
        }
    } catch (std::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        std::cerr << "Response (truncated): " << response.substr(0, 300) << "...\n";
    }

    return roads;
}



std::vector<std::vector<int>> roadsToMatrix( const std::vector<OSMRoad>& roads, int gridHeight, int gridWidth) {
    if (roads.empty()) {
        return {};
    }

    double minLat = 999, maxLat = -999;
    double minLon = 999, maxLon = -999;

    for (const auto& road : roads) {
        for (const auto& [lat, lon] : road.coordinates) {
            minLat = std::min(minLat, lat);
            maxLat = std::max(maxLat, lat);
            minLon = std::min(minLon, lon);
            maxLon = std::max(maxLon, lon);
        }
    }


    std::vector<std::vector<int>> grid(gridHeight, std::vector<int>(gridWidth, 0));

    auto latToY = [&](double lat) {
        return static_cast<int>(
            (1.0 - (lat - minLat) / (maxLat - minLat) + 0.000001) * (gridHeight - 1)
        );
    };
    auto lonToX = [&](double lon) {
        return static_cast<int>(
            ((lon - minLon) / (maxLon - minLon) + 0.000001) * (gridWidth - 1)
        );
    };



    for (const auto& road : roads) {
        for (const auto& [lat, lon] : road.coordinates) {
            int y = latToY(lat);
            int x = lonToX(lon);
            if (y >= 0 && y < gridHeight && x >= 0 && x < gridWidth) {
                grid[y][x] = 1;
            }
        }
    }

    return grid;
}