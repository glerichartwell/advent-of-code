/**
 * @file day2.cc
 * @author Eric Hartwell
 * @date 2023
 * 
 * This file contains the solutions for Day 2
 * 
*/

#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <tuple>

using namespace std;
namespace game {
    map<string, int> cubeCheck {{"blue", 14}, {"green", 13}, {"red", 12}};

    const int POSSIBLE = 1;
    const int IMPOSSIBLE = 0;
    
    tuple<int, string> extractGameData(string game) {
        int colonIdx = game.find(':');

        string gameData = game.substr(0, colonIdx);
        int gameID = stoi(gameData.erase(0, 5)); // extract game ID
        
        string rounds = game.substr(colonIdx + 1); // extract rounds

        return {gameID, rounds};
    }

    int playRound(string round) {
        
        stringstream roundStream(round);
        string cubes;
        
        while (getline(roundStream, cubes, ',')) {
            string numString;
            string color;
            stringstream(cubes) >> numString >> color;
            int numCubes = stoi(numString);
            if (numCubes > cubeCheck[color])
                return IMPOSSIBLE;

        }

        return POSSIBLE;
    }

    int playGame(string rounds ) {
        
        stringstream gameStream(rounds);
        string round;
        
        while (getline(gameStream, round, ';')) {
            if (playRound(round) == IMPOSSIBLE)
                return IMPOSSIBLE;
        }

        return POSSIBLE;
    }

    tuple<int, int, int> updateFewestCubes(string round, tuple<int, int, int> maxes) {
        stringstream roundStream(round);
        string cubes;
        auto [blueMax, greenMax, redMax] = maxes;
        while (getline(roundStream, cubes, ',')) {
            
            string numString;
            string color;
            stringstream(cubes) >> numString >> color;
            int numCubes = stoi(numString);

            if (color == "blue") {
                blueMax = numCubes > blueMax ? numCubes : blueMax;
            } else if (color == "green") {
                greenMax = numCubes > greenMax ? numCubes : greenMax;
            } else if (color == "red") {
                redMax = numCubes > redMax ? numCubes : redMax;
            }

        }

        return {blueMax, greenMax, redMax};
    }

    int calcSetPower(string rounds) {
        stringstream gameStream(rounds);
        string round;
        tuple<int, int, int> maxes{0, 0, 0};
        int setPower = 0;
        while (getline(gameStream, round, ';')) {
            maxes = updateFewestCubes(round, maxes);
        }
        auto [blue, green, red] = maxes;
        setPower = blue * green * red;
        return setPower;
    }
}

int partOne() {

    ifstream inputFile;
    inputFile.open("input.txt");

    int idSum = 0;
    string game;
    while (getline(inputFile, game)) {
        auto [gameID, rounds] = game::extractGameData(game);
        if (game::playGame(rounds) == game::POSSIBLE) 
            idSum += gameID;
    }

    inputFile.close();
    return idSum;
}

int partTwo() {
    ifstream inputFile;
    inputFile.open("input.txt");

    int setPowerSum = 0;
    string game;
    while (getline(inputFile, game)) { 
        auto [gameID, rounds] = game::extractGameData(game);
        setPowerSum += game::calcSetPower(rounds);
    }

    inputFile.close();
    return setPowerSum;
}


int main() {
    
    cout << "Day 2 Part 1: " << partOne() << endl;
    cout << "Day 2 Part 2: " << partTwo() << endl;

    return 0;
}


