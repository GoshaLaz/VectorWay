#include "vectorway/open_street_maps.h"
#include "vectorway/library.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


int main() {
    double south = 50.45000;
    double west  = 30.52390;
    double north = 50.45070;
    double east  = 30.52470;


    cout << "position for start DFS:" << "\n";
    int startX, startY;
    cin >> startX >> startY;

    cout << "position for start and finish Dijkstra:" << "\n";
    int startX2, startY2;
    cin >> startX2 >> startY2;
    int endX, endY;
    cin >> endX >> endY;

    auto matrix = roadsToMatrix(getRoadsFromOSM(south, west, north, east),8, 8);
    auto id = [&](int x, int y) {
        return x * static_cast<int>(matrix.size()) + y;
    };
    auto dfsResult = dfs(startX, startY, matrix);
    auto [dist, parent] = dijkstra_to(matrixToGraph(matrix), id(startX2, startY2), id(endX, endY));
    auto path = restore_path(id(startX2, startY2), id(endX, endY), parent);


    cout << "Matrix:\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    for (auto p : dfsResult) {
        cout << p.first << " " << p.second << "\n";
    }

    RenderWindow window(VideoMode({804, 804}), "Example VectorWay");

    vector<vector<RectangleShape>> squares;
    for (int i = 0; i < 8; i++) {
        vector<RectangleShape> temp;
        for (int j = 0; j < 8; j++) {
            Color colorSquare;
            if (matrix[i][j] == 1) {
                colorSquare = Color::Red;
            }
            else {
                colorSquare = Color::White;
            }
            RectangleShape square(Vector2f(96, 96));
            square.setFillColor(colorSquare);
            square.setOutlineColor(Color(145, 145,145));
            square.setOutlineThickness(4);
            square.setPosition(Vector2f(static_cast<float>(i) * 100 + 4, static_cast<float>(j) * 100 + 4));
            temp.push_back(square);
        }
        squares.push_back(temp);
    }

    auto squares2 = squares;

    Clock clock;
    Clock clock2;
    int cnt = 1;
    int cnt2 = 1;
    Color dfsSquare = Color(50, 130, 246);
    Color dijkSquare = Color(50, 130, 246);

    bool waitStart = false;
    bool waitStart2 = false;
    bool flag = false;

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.clear();


        if (!flag) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    window.draw(squares[i][j]);
                }
            }

            if (clock.getElapsedTime().asSeconds() >= 3.f) {
                waitStart = true;
                clock.restart();
            }

            if (cnt == 1 && waitStart) {
                int i = dfsResult[0].first;
                int j = dfsResult[0].second;
                squares[i][j].setFillColor(dfsSquare);
            }
            if (clock.getElapsedTime().asSeconds() >= 1.f && cnt < dfsResult.size() && waitStart) {
                int i = dfsResult[cnt - 1].first;
                int j = dfsResult[cnt - 1].second;
                squares[i][j].setFillColor(Color(115, 251, 253));
                i = dfsResult[cnt].first;
                j = dfsResult[cnt].second;
                squares[i][j].setFillColor(dfsSquare);
                cnt++;
                clock.restart();
            }

            if (cnt >= dfsResult.size() && clock.getElapsedTime().asSeconds() >= 2.f) {
                flag = true;
                clock.restart();
            }
        }
        else {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    window.draw(squares2[i][j]);
                }
            }
            if (clock2.getElapsedTime().asSeconds() >= 3.f) {
                waitStart2 = true;
                clock2.restart();
            }
            if (cnt2 == 1 && waitStart2) {
                int i = path[0] / 8;
                int j = path[0] % 8;
                squares2[i][j].setFillColor(dijkSquare);
            }
            if (clock2.getElapsedTime().asSeconds() >= 1.f && cnt2 < path.size() && waitStart2) {
                int i = path[cnt2 - 1] / 8;
                int j = path[cnt2 - 1] % 8;
                squares2[i][j].setFillColor(Color(115, 251, 253));
                i = path[cnt2] / 8;
                j = path[cnt2] % 8;
                squares2[i][j].setFillColor(dijkSquare);
                cnt2++;
                clock2.restart();
            }
        }


        window.display();
    }



    return 0;
}