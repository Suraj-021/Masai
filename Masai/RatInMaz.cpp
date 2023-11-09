#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 10; // Adjust the size of the maze (N x N) as needed

vector<vector<char>> generateMaze()
{
    vector<vector<char>> maze(N, vector<char>(N));
    int wallPercentage = 25;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == 0 && j == 0)
            {
                maze[i][j] = 'S'; // Start
            }
            else if (i == N - 1 && j == N - 1)
            {
                maze[i][j] = 'E'; // End
            }
            else if (rand() % 100 < wallPercentage)
            {
                maze[i][j] = '█'; // Wall
            }
            else
            {
                maze[i][j] = '◌'; // Open Space
            }
        }
    }

    return maze;
}

void printMaze(const vector<vector<char>> &maze)
{
    for (const auto &row : maze)
    {
        for (char cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
}

bool dfs(vector<vector<char>> &maze, vector<vector<char>> &pathMaze, vector<vector<bool>> &visited, int row, int col)
{
    int N = maze.size();

    if (row < 0 || row >= N || col < 0 || col >= N || visited[row][col] || maze[row][col] == '█')
    {
        return false;
    }

    if (maze[row][col] == 'E')
    {
        return true;
    }

    visited[row][col] = true;

    // Try moving in all four directions (up, down, left, right)
    if (dfs(maze, pathMaze, visited, row - 1, col) ||
        dfs(maze, pathMaze, visited, row + 1, col) ||
        dfs(maze, pathMaze, visited, row, col - 1) ||
        dfs(maze, pathMaze, visited, row, col + 1))
    {
        pathMaze[row][col] = '◍'; // Mark the path
        return true;
    }

    return false;
}

vector<vector<char>> findPath(vector<vector<char>> &maze)
{
    int N = maze.size();
    vector<vector<char>> pathMaze(N, vector<char>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            pathMaze[i][j] = maze[i][j];
        }
    }
    vector<vector<bool>> visited(N, vector<bool>(N, false));

    if (dfs(maze, pathMaze, visited, 0, 0))
    {
        return pathMaze;
    }
    else
    {
        cout << "No path found!" << endl;
        return maze;
    }
}

int main()
{
    srand(time(nullptr)); // Seed the random number generator

    vector<vector<char>> maze = generateMaze();

    while (true)
    {
        printMaze(maze);
        cout << "Options:" << endl;
        cout << "1. Print Path" << endl;
        cout << "2. Generate Another Maze" << endl;
        cout << "3. Exit" << endl;
        cout << "Select an option: ";

        int option;
        cin >> option;
        cin.ignore(); // Consume the newline character

        if (option == 1)
        {
            vector<vector<char>> pathMaze = findPath(maze);
            printMaze(pathMaze);
        }
        else if (option == 2)
        {
            maze = generateMaze();
        }
        else if (option == 3)
        {
            cout << "Exiting Maze Solver. Goodbye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}