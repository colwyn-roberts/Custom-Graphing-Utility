#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
namespace players
{
    class Player
    {
    public:
        string name;
        vector<int> kills;
        vector<int> deaths;
        vector<int> assists;
        vector<int> damage;
        vector<int> accuracy;
        vector<int> healing;
        vector<string> heros;
        //debug info, returns entire object formated for printing
        std::string toString() {
            std::string output = "[PLAYER]\n";
            output += "string name = " + name + "\n";

            for (int i = 0; i < kills.size(); i++) {
                output += "[" + std::to_string(i) + "] | K/D/A: " + std::to_string(kills.at(i)) + "/" + std::to_string(deaths.at(i)) + "/" + std::to_string(assists.at(i));
                output += " | H/D: " + std::to_string(healing.at(i)) + "/" + std::to_string(damage.at(i)) + " | accuracy: " + std::to_string(accuracy.at(i)) + "%\n";
            }
            return output;
        }
    };

}
