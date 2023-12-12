/**
 * @file day1.cc
 * @author Eric Hartwell
 * @date 2023
 * 
 * This file contains the solutions for Day 1
 * 
*/
    
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;
namespace game {
    map<string, int> cubeCheck {{"blue", 14}, {"green", 13}, {"red", 12}};

    const int POSSIBLE = 1;
    const int IMPOSSIBLE = 0;
    
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
}

int partOne() {

    

    ifstream inputFile;
    inputFile.open("input.txt");

    int idSum = 0;
    string game;
    while (getline(inputFile, game)) {
        
        int colonIdx = game.find(':');

        string gameData = game.substr(0, colonIdx);
        int gameID = stoi(gameData.erase(0, 5)); // extract game ID
        
        string rounds = game.substr(colonIdx + 1); // extract rounds

        if (game::playGame(rounds) == game::POSSIBLE) 
            idSum += gameID;

        
    }
    inputFile.close();
    return idSum;
}


int main() {
    cout << "Day 2 Part 1: " << partOne() << endl;

    return 0;
}


