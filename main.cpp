#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <functional>
#include <math.h>
#include <float.h>
#include <vector>
#include <set>
#include <string.h>
#include <string>
#include <sstream>
using namespace std;
using namespace sf;
#define sz 60

int pathlen;
vector<pair<int, int>> path;
bool sptSet[sz][sz]; // explored set
void findMin(float dist[sz][sz], int &min_x, int &min_y)
{
    float mini = FLT_MAX;
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            if (sptSet[i][j] == false && dist[i][j] < mini)
            {
                mini = dist[i][j];
                min_x = i;
                min_y = j;
            }
}
void makePath(pair<int, int> previous[sz][sz], float dist[sz][sz], int dest_x, int dest_y, int source_x, int source_y)
{
    cout << "\nLength of Dijkstra path is: " << dist[dest_x][dest_y] << endl;
    pathlen=int(dist[dest_x][dest_y]);
    while (previous[dest_x][dest_y].first != source_x || previous[dest_x][dest_y].second != source_y)
    {                                // both simultaneously equal to source coordinates
        sf::sleep(milliseconds(10)); // delay shortest path display
        cout << "go to -> (" << previous[dest_x][dest_y].first << "," << previous[dest_x][dest_y].second << ") \n";
        if (previous[dest_x][dest_y].first == 0 && previous[dest_x][dest_y].second == 0)
            break;
        path.push_back({previous[dest_x][dest_y].first, previous[dest_x][dest_y].second});
        int save_x = dest_x, save_y = dest_y;
        dest_x = previous[save_x][save_y].first;
        dest_y = previous[save_x][save_y].second;
    }
}

void dijkstra(int source_x, int source_y, int dest_x, int dest_y, int grid[sz][sz])
{
    pair<int, int> previous[sz][sz];
    float dist[sz][sz];
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            dist[i][j] = FLT_MAX;
    dist[source_x][source_y] = 0.0;
    int found = 0;
    for (int i = 0; i < sz && found == 0; i++)
        for (int j = 0; j < sz && found == 0; j++)
        {
            int min_x = 0, min_y = 0;
            findMin(dist, min_x, min_y);
            sptSet[min_x][min_y] = true;
            if (sptSet[dest_x][dest_y] == true)
            {
                found = 1;
                break;
            }
            sf::sleep(milliseconds(1)); // delay
            // up
            if (grid[min_x - 1][min_y] == 1 && sptSet[min_x - 1][min_y] == false && dist[min_x - 1][min_y] > dist[min_x][min_y] + 1.0)
            {
                dist[min_x - 1][min_y] = dist[min_x][min_y] + 1.0;
                previous[min_x - 1][min_y] = make_pair(min_x, min_y);
            }
            // down
            if (grid[min_x + 1][min_y] == 1 && sptSet[min_x + 1][min_y] == false && dist[min_x + 1][min_y] > dist[min_x][min_y] + 1.0)
            {
                dist[min_x + 1][min_y] = dist[min_x][min_y] + 1.0;
                previous[min_x + 1][min_y] = make_pair(min_x, min_y);
            }
            // left
            if (grid[min_x][min_y - 1] == 1 && sptSet[min_x][min_y - 1] == false && dist[min_x][min_y - 1] > dist[min_x][min_y] + 1.0)
            {
                dist[min_x][min_y - 1] = dist[min_x][min_y] + 1.0;
                previous[min_x][min_y - 1] = make_pair(min_x, min_y);
            }
            // right
            if (grid[min_x][min_y + 1] == 1 && sptSet[min_x][min_y + 1] == false && dist[min_x][min_y + 1] > dist[min_x][min_y] + 1.0)
            {
                dist[min_x][min_y + 1] = dist[min_x][min_y] + 1.0;
                previous[min_x][min_y + 1] = make_pair(min_x, min_y);
            }
            // up and right:i-1,j+1
            if (grid[min_x - 1][min_y + 1] == 1 && sptSet[min_x - 1][min_y + 1] == false &&
                dist[min_x - 1][min_y + 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x - 1][min_y] == 0 && grid[min_x][min_y + 1] == 0))
            {
                dist[min_x - 1][min_y + 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x - 1][min_y + 1] = make_pair(min_x, min_y);
            }
            // down and right:i+1,j+1
            if (grid[min_x + 1][min_y + 1] == 1 && sptSet[min_x + 1][min_y + 1] == false &&
                dist[min_x + 1][min_y + 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x + 1][min_y] == 0 && grid[min_x][min_y + 1] == 0))
            {
                dist[min_x + 1][min_y + 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x + 1][min_y + 1] = make_pair(min_x, min_y);
            }
            // down and left:i+1,j-1
            if (grid[min_x + 1][min_y - 1] == 1 && sptSet[min_x + 1][min_y - 1] == false &&
                dist[min_x + 1][min_y - 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x + 1][min_y] == 0 && grid[min_x][min_y - 1] == 0))
            {
                dist[min_x + 1][min_y - 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x + 1][min_y - 1] = make_pair(min_x, min_y);
            }
            // up and left:i-1,j-1
            if (grid[min_x - 1][min_y - 1] == 1 && sptSet[min_x - 1][min_y - 1] == false &&
                dist[min_x - 1][min_y - 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x - 1][min_y] == 0 && grid[min_x][min_y - 1] == 0))
            {
                dist[min_x - 1][min_y - 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x - 1][min_y - 1] = make_pair(min_x, min_y);
            }
        }
    makePath(previous, dist, dest_x, dest_y, source_x, source_y);
}

int main()
{
    int filled[sz][sz];
    int grid[60][60];
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            if (i == 0 || i == 59 || j == 0 || j == 59) // walls
                grid[i][j] = 0;
            else
                grid[i][j] = 1;
        }
    }

    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            sptSet[i][j] = false;
            filled[i][j] = 0;
        }
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Dijkstra Visualizer");

    sf::Font font;
    font.loadFromFile("VT323-Regular.ttf");
    sf::Text text("Start", font, 22);
    sf::Text len("Length:", font, 22);
    sf::Text clr("Clear", font, 22);
    sf::Text length(" ", font, 44);
    sf::Text desc("This is a Dijkstra's Visualizer \n\n > Left Click to place Obstacles \n\n > Space to Quit \n\n (Work In Progress)", font, 15);

    RectangleShape buttonStart(Vector2f(75, 25)); // start
    buttonStart.setFillColor(Color::Red);

    RectangleShape buttonClr(Vector2f(75, 25)); // clear
    buttonClr.setFillColor(Color::Blue);

    RectangleShape rectangle(Vector2f(10, 10)); // default box :White
    rectangle.setFillColor(Color::White);
    RectangleShape brectangle(Vector2f(10, 10)); // Black box
    brectangle.setFillColor(Color::Black);
    RectangleShape grectangle(Vector2f(10, 10)); // Green
    grectangle.setFillColor(Color::Green);
    grectangle.setOutlineThickness(2);
    grectangle.setOutlineColor(Color::Black);

    RectangleShape blueRectangle(Vector2f(10, 10));
    blueRectangle.setFillColor(Color::Blue);
    blueRectangle.setOutlineThickness(2);
    blueRectangle.setOutlineColor(Color::Red);
    RectangleShape rrectangle(Vector2f(10, 10));
    rrectangle.setFillColor(Color::Red);
    rrectangle.setOutlineThickness(2);
    rrectangle.setOutlineColor(Color::Red);
    RectangleShape yrectangle(Vector2f(10, 10));
    yrectangle.setFillColor(Color::Yellow);

    int source_x = 2, source_y = 2, dest_x = 57, dest_y = 57;
    Thread thread(bind(&dijkstra, source_x, source_y, dest_x, dest_y, grid));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                window.close();

            // if(event.type==Event::MouseButtonPressed&&event.mouseButton.button==Mouse::Right){
            //     int X=event.mouseButton.x;
            //     int Y=event.mouseButton.y;
            //     int row=Y/10;       //Reversed notion of row & column
            //     int col=X/10;
            //     source_x=row;
            //     source_y=col;
            // }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
            {
                int X = event.mouseButton.x;
                int Y = event.mouseButton.y;
                int row = Y / 10; // Reversed notion of row & column
                int col = X / 10;
                dest_x = row;
                dest_y = col;
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                int X = event.mouseButton.x;
                int Y = event.mouseButton.y;
                if (X > 650 && X < 725 && Y > 250 && Y < 275)
                {
                    for (int i = 0; i < 60; i++)
                    {
                        for (int j = 0; j < 60; j++)
                        {
                            if (i == 0 || i == 59 || j == 0 || j == 59) // walls
                                grid[i][j] = 0;
                            else
                                grid[i][j] = 1;
                        }
                    }

                    for (int i = 0; i < sz; i++)
                    {
                        for (int j = 0; j < sz; j++)
                        {
                            sptSet[i][j] = false;
                            filled[i][j] = 0;
                        }
                    }
                    path.clear();
                }

                if ((X < 590 && X > 10 && Y < 590 && Y > 10) || (X > 650 && X < 725 && Y > 100 && Y < 125))
                {
                    int row = Y / 10; // Reversed notion of row & column
                    int col = X / 10;
                    if (grid[row][col] == 0 && row < 60 && col < 60)
                        grid[row][col] = 1;
                    else if (row < 60 && col < 60)
                        grid[row][col] = 0;
                    cout << "Cell " << row << " , " << col << " state is: " << grid[row][col] << endl;
                    if (X > 650 && X < 725 && Y > 100 && Y < 125)
                    {
                        thread.launch(); // launching dijkstra
                        // dijkstra(source_x, source_y, dest_x, dest_y, grid);
                    }
                }
            }
        }

        window.clear();
        buttonStart.setPosition(650, 100);
        window.draw(buttonStart); // Dijkstra launch

        buttonClr.setPosition(650, 250);
        window.draw(buttonClr); // clear

        clr.setPosition(665, 247);

        text.setPosition(665, 97); // Dijkstra text
        len.setPosition(640, 160);
        length.setPosition(710, 143); // Display Dijkstra length

        desc.setPosition(600, 350);

        window.draw(text);
        stringstream ss1;
        ss1 << path.size(); //or pathlen int to string
        length.setString(ss1.str());

        window.draw(length);
        window.draw(len);
        window.draw(clr);
        window.draw(desc);
        if (!path.empty())
        {
            for (int i = 0; i < path.size(); i++)
            {
                blueRectangle.setPosition(path[i].second * 10, path[i].first * 10); // Reversed notion of row & column
                window.draw(blueRectangle);                                         // final path
                filled[path[i].first][path[i].second] = 1;
            }
        }
        grectangle.setPosition(source_y * 10, source_x * 10);
        window.draw(grectangle); // source
        filled[source_x][source_y] = 1;
        rrectangle.setPosition(dest_y * 10, dest_x * 10);
        window.draw(rrectangle); // destination
        filled[dest_x][dest_y] = 1;
        for (int i = 0; i <= 590; i += 10)
            for (int j = 0; j <= 590; j += 10)
            {
                if (grid[i / 10][j / 10] == 0)
                {
                    brectangle.setOutlineThickness(2);
                    brectangle.setOutlineColor(Color::Black);
                    brectangle.setPosition(j, i);
                    window.draw(brectangle); // User's obstacle
                }
                if (sptSet[i / 10][j / 10] == true && filled[i / 10][j / 10] == 0)
                {
                    yrectangle.setOutlineThickness(2);
                    yrectangle.setOutlineColor(Color::Black);
                    yrectangle.setPosition(j, i);
                    window.draw(yrectangle); // Explored Cells by dijkstra
                }

                if (grid[i / 10][j / 10] == 1 && sptSet[i / 10][j / 10] == false && filled[i / 10][j / 10] == 0)
                { // not in dijkstra
                    rectangle.setOutlineThickness(2);
                    rectangle.setOutlineColor(Color::Black);
                    rectangle.setPosition(j, i);
                    window.draw(rectangle); // default white cells
                }
            }

        window.display();
    }

    return 0;
}