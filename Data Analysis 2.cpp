// Data Analysis 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include "Player.h"
#include "ImageCreator.h"
#include <Windows.h>
#include <cstdint>
#include <wingdi.h>
#include "Pixel.h"
//#include "StatScraper.cpp";
using namespace std;
using namespace players;
using namespace image;

double findAverage(int start, int end, vector<double> stat) {
    int output = 0;
    for (int i = start; i < end; i++) {
        output += stat.at(i);
    }
    output /= end-start;
    return output;
}

double findAverage(int start, int end, vector<int> stat) {
    int output = 0;
    for (int i = start; i < end; i++) {
        output += stat.at(i);
    }
    output /= end - start;
    return output;
}

void findMinMax(int* min, int* max, vector<int> stat) {
    *min = stat.at(0);
    *max = stat.at(0);
    for (int i = 1; i < stat.size(); i++) {
        if (stat.at(i) > *max) {
            *max = stat.at(i);
        }
        if (stat.at(i) < *min) {
            *min = stat.at(i);
        }
    }
}

void findMinMax(double* min, double* max, vector<double> stat) {
    *min = stat.at(0);
    *max = stat.at(0);
    for (int i = 1; i < stat.size(); i++) {
        if (stat.at(i) > *max) {
            *max = stat.at(i);
        }
        if (stat.at(i) < *min) {
            *min = stat.at(i);
        }
    }
}

void vectorDoubleConversion(vector<int>* input, vector<double>* output) {
    for (int i = 0; i < input->size(); i++) {
        (*output).push_back((double)((*input).at(i)));
    }
}

void drawGraph(string name, vector<double> stat,Pixel pixel, int forceMin = -1, int forceMax = -1, bool drawScale = true, int xScale = -1, bool filled = true, bool plotLines = true) {
    //Grid Line Colours;
    Pixel gridLinePixel = Pixel(200,200,200);
    uint8_t opacity = 10;
    const double GRID_LINE_V_NUM = 10; //vertical lines
    const double GRID_LINE_H_NUM = 10; //horizontal lines

    //boundarys for graph
    const double AXIS_POS_X = 200;
    const double AXIS_POS_Y = 100;
    const double GRAPH_MAX_Y = ImageCreator::BmpInfoHeader().height - 50;
    const double GRAPH_MAX_X = ImageCreator::BmpInfoHeader().width - 50;
    const int CHAR_LIMIT_X = 3; //includes '.'
    const int CHAR_LIMIT_Y = 4; 
    const int LINE_WIDTH = 1;
    const int TEXT_SIZE = 5;
    const int TEXT_X_OFFSET = 30;
    const int TEXT_Y_OFFSET = 50;

    //adds title
    if (drawScale) {
        ImageCreator::addText(15, GRAPH_MAX_Y + 15, name + " stat average", TEXT_SIZE, 1);
    }

    //finds scale of graph
    double min, max;
    findMinMax(&min, &max, stat);
    if (forceMin != -1) {
        min = forceMin;
    }
    if (forceMax != -1) {
        max = forceMax;
    }
    int pointNum = stat.size();
    //std::cout << "\nmax: " << max << " | min: " << min;
    double unitSizeY = ((max - min) / GRID_LINE_H_NUM);
    double unitSizeX = pointNum/ GRID_LINE_V_NUM;
    //std::cout <<"\nunitSizeX: " << unitSizeX;
    //std::cout << "\nunitSizeY: " << unitSizeY;
    if (drawScale) {
        //draws horizontal grid lines
        for (int i = 0; i < GRID_LINE_H_NUM; i++) {
            int cX = (int)((i * (((GRAPH_MAX_Y - AXIS_POS_Y))) / (GRID_LINE_H_NUM))) + AXIS_POS_Y;
            if (to_string((unitSizeY * i) + min).substr(0, CHAR_LIMIT_Y)[CHAR_LIMIT_Y - 1] == '.' or (unitSizeY * i) == (int)(unitSizeY * i)) { //ensures string doesnt end with '.' or is int
                ImageCreator::addText(AXIS_POS_X - TEXT_X_OFFSET, cX, to_string(((int)(unitSizeY * i) + min)).substr(0, CHAR_LIMIT_Y + 1), TEXT_SIZE, 2);
            }
            else {
                ImageCreator::addText(AXIS_POS_X - TEXT_X_OFFSET, cX, to_string((unitSizeY * i) + min).substr(0, CHAR_LIMIT_Y), TEXT_SIZE, 2);
            }

            for (double ii = AXIS_POS_X; ii <= GRAPH_MAX_X; ii++) {
                ImageCreator::addPixel(cX, (int)ii, gridLinePixel);
            }
        }
        //draws vertical grid lines 
        for (int i = 0; i < GRID_LINE_V_NUM; i++) {
            int cY = (int)(i * ((GRAPH_MAX_X - AXIS_POS_X) / (GRID_LINE_V_NUM))) + AXIS_POS_X;
            if (to_string((unitSizeX * i) + min).substr(0, CHAR_LIMIT_X)[CHAR_LIMIT_X - 1] == '.' or (unitSizeX * i) == (int)(unitSizeX * i)) { //ensures string doesnt end with '.' or is int
                ImageCreator::addText(cY, AXIS_POS_Y - TEXT_Y_OFFSET, to_string((unitSizeX * i)).substr(0, CHAR_LIMIT_X + 1), TEXT_SIZE, 1);
            }
            else {
                ImageCreator::addText(cY, AXIS_POS_Y - TEXT_Y_OFFSET, to_string((unitSizeX * i)).substr(0, CHAR_LIMIT_X), TEXT_SIZE, 1);
            }
            for (double ii = AXIS_POS_Y; ii <= GRAPH_MAX_Y; ii++) {
                ImageCreator::addPixel((int)ii, cY, gridLinePixel);
            }
        }
    }
    if (plotLines) {
        vector<double> pointYPos;
        vector<double> pointXPos;
        if (xScale == -1) {
            xScale = stat.size();
        }
        //Adds points onto 
        for (int i = 0; i < stat.size(); i++) {
            double unitToPixel = (GRAPH_MAX_Y - AXIS_POS_Y) / (max - min);
            double y = ((stat.at(i) - min) * ((unitToPixel))) + AXIS_POS_Y;
            double x = ((i + 1) * ((GRAPH_MAX_X - AXIS_POS_X) / (xScale))) + AXIS_POS_X;//i+1 shifts from starting at 0 -> 1
            ImageCreator::drawCircle(x, y, 2, pixel);
            pointYPos.push_back(y);
            pointXPos.push_back(x);
        }
        if (filled) {
            //draws connecting lines
            double unitToPixel = ((GRAPH_MAX_X - AXIS_POS_X) / stat.size());
            double deltaY;
            for (int i = 0; i < pointYPos.size() - 1; i++) {
                //std::cout << "\n1:(" << pointXPos.at(i) << "," << pointYPos.at(i) << ") | 2: (" << pointXPos.at(i + 1) << "," << pointYPos.at(i + 1) << ")";
                ImageCreator::drawTriangle(pointXPos.at(i), pointYPos.at(i), pointXPos.at(i + 1), pointYPos.at(i + 1), AXIS_POS_Y, LINE_WIDTH, pixel, opacity);
            }
            //line to 0
            ImageCreator::drawTriangle(AXIS_POS_X, AXIS_POS_Y, pointXPos.at(0), pointYPos.at(0), AXIS_POS_Y, LINE_WIDTH, pixel, opacity);
        }
        else {
            for (int i = 0; i < pointYPos.size() - 1; i++) {
                //std::cout << "\n1:(" << pointXPos.at(i) << "," << pointYPos.at(i) << ") | 2: (" << pointXPos.at(i + 1) << "," << pointYPos.at(i + 1) << ")";
                ImageCreator::drawLine(pointXPos.at(i), pointYPos.at(i), pointXPos.at(i + 1), pointYPos.at(i + 1), LINE_WIDTH, pixel);
            }
            ImageCreator::drawLine(AXIS_POS_X, AXIS_POS_Y, pointXPos.at(0), pointYPos.at(0), LINE_WIDTH, pixel);
        }
    }
}

void drawGraph(string name, vector<int> stat, Pixel pixel, int forceMin = -1, int forceMax = -1, bool drawScale = true, int xScale = -1, bool filled = true, bool plotLines = true) {
    vector<double> statDouble;
    vectorDoubleConversion(&stat, &statDouble);
    drawGraph(name, statDouble, pixel, forceMin, forceMax, drawScale, xScale, filled, plotLines);
}

void drawAverageGraph(string name, vector<int> stat, Pixel pixel, int forceMin = -1, int forceMax = -1, bool drawScale = true, int xScale = -1, bool shaded = false,int range = -1) {
    vector<double> average;
    double total = 0;
    if (range > 0) {
        for (int i = 0; i < stat.size(); i++) {
            total += stat.at(i);
            //cout << "\nstat: " << stat.at(i) << " | running average: " << total / (i + 1); //i+1 converts from index to actual item number
            if (i > range) {
                total -= stat.at(i - range);
                average.push_back(total / range);
            }
            else {
                average.push_back(total / (i + 1));
            }
        }
    }
    else {
        for (int i = 0; i < stat.size(); i++) {
            total += stat.at(i);
            //cout << "\nstat: " << stat.at(i) << " | running average: " << total / (i + 1); //i+1 converts from index to actual item number
            average.push_back(total / (i + 1));
        }
    }
    drawGraph(name, average, pixel, forceMin, forceMax, drawScale,xScale,shaded);
}

void stackGraphs(string name, vector<vector<int>> stats, int forceMin = -1, int forceMax = -1,int range = -1) {
    int trueMax = INT32_MIN;
    int trueMin = INT32_MAX;
    int maxLength = 0;
    vector<int> indexOrder;
    vector<double> allAverages;
    int index = 0;
    for (vector<int> stat : stats) {
        int min, max, avg;
        avg = findAverage(0, stat.size(), stat);
        findMinMax(&min, &max, stat);
        if (min < trueMin) {
            trueMin = min;
        }
        if (max > trueMax) {
            trueMax = max;
        }
        if (stat.size() > maxLength) {
            maxLength = stat.size();
        }
        allAverages.push_back(avg);
        indexOrder.push_back(index);
        index++;
    }
    bool hasSwapped = true;
    while (hasSwapped) {
        hasSwapped = false;
        for (int i = 0; i < allAverages.size()-1; i++) {
            if (allAverages.at(i) < allAverages.at(i + 1)) {
                double temp = allAverages.at(i+1); //swaps averages
                allAverages.at(i + 1) = allAverages.at(i);
                allAverages.at(i) = temp;
                temp = indexOrder.at(i+1); //tracks original index locations to new ones
                indexOrder.at(i + 1) = indexOrder.at(i);
                indexOrder.at(i) = temp;
                hasSwapped = true;
            }
        }
    }
    //std::cout << "\nAll averages: [";
    for (int i = 0; i < allAverages.size(); i++) {
        std::cout << allAverages.at(i) << ",";
    }
    //std::cout << "]";
    //std::cout << "\index Order: [";
    for (int i = 0; i < indexOrder.size(); i++) {
        std::cout << indexOrder.at(i) << ",";
    }
    //std::cout << "]";

    //std::cout << "(min,max): (" << trueMin << "," << trueMax << ")\n";


    Pixel graphColours[10] = {Pixel(255,0,0),Pixel(255,255,0),Pixel(0,0,255),Pixel(255,0,255)}; //just a list of colours
    //fills area under graph
    for (int i = 0; i < stats.size(); i++) {
        Pixel pixel = graphColours[i];
        //std::cout << "\norder index: " << indexOrder.at(i);
        drawAverageGraph(name, stats.at(indexOrder.at(i)), pixel, trueMin, trueMax, false, maxLength,false, range);
    }
    drawGraph(name, stats.at(indexOrder.at(0)), Pixel(0, 0, 0), trueMin, trueMax, true, maxLength, false, false); //draws grid
    //goes back over and highlights lines and points
    for (int i = 0; i < stats.size(); i++) {
        Pixel pixel = graphColours[i];
        drawAverageGraph(name, stats.at(indexOrder.at(i)), pixel, trueMin, trueMax, false, maxLength, false, range);
    }
}

void findAttribute(string attribute, vector<int>* outputArray, ifstream* file) {
    cout << "\nAttribute: " << attribute << "\n";
    string line;
    int progressBarStatus = 1;
    while (getline(*file, line)) {
        size_t location = line.find("Premium users don't see ads."); //skips all the gibberish before all the match data
        if (location != string::npos) {
            location += (size_t)28;
            location += line.substr(location).find("Premium users don't see ads."); //needs the second time this apears, for all the gibberish to be skipped
            if (location != string::npos) {
                size_t nextLocation = 0;
                while (nextLocation != string::npos) {
                    string attributeHeader = "class=\"truncate\">" + attribute;
                    nextLocation = line.substr(location).find(attributeHeader);
                    location += nextLocation;
                    if (nextLocation != string::npos) { //checks to see if you are adding npos, NOT that the location after adding is npos because it will loop over from npos to a normal number
                        location += (size_t)23; //offsets what was already there
                        nextLocation = line.substr(location).find("class=\"truncate\">");
                        location += nextLocation;
                        if (nextLocation != string::npos) {
                            location += (size_t)17; //also offsets
                            size_t nextEndChar = line.substr(location).find("<");
                            if (nextEndChar != string::npos) {
                                if (line.substr(location, nextEndChar - 1)[0] < 58) { //ensures that the first character is a number
                                    if (true/*(*outputArray).size() < 1000*/) {
                                        (*outputArray).push_back(stoi(line.substr(location, nextEndChar - 1)));
                                    }
                                    else {
                                        break;
                                    }
                                    //progress bar
                                    if ((1-((line.size() - (double)location) / line.size())) * 10 >= progressBarStatus) {
                                        cout << "#";
                                        progressBarStatus++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else {
                std::cout << "\n-------------------------------\nFound only 1 'Premium users don't see ads.'. Bad File Input\n-------------------------------\n";
                throw std::invalid_argument("Found only 1 'Premium users don't see ads.'. Bad File Input");
            }
        }
    }
}

void findHeros(vector<string>* outputArray, ifstream* file) {
    cout << "\nLooking for Heros\n";
    string line;
    int i = 0;
    int progressBarStatus = 1;
    while (getline(*file, line)) {
        size_t location = line.find("Premium users don't see ads."); //skips all the gibberish before all the match data
        if (location != string::npos) {
            location += (size_t)28;
            location += line.substr(location).find("Premium users don't see ads."); //needs the second time this apears, for all the gibberish to be skipped
            if (location != string::npos) {
                size_t nextLocation = 0;
                while (nextLocation != string::npos) {
                    string attributeHeader = "alt=\"";
                    nextLocation = line.substr(location).find(attributeHeader);
                    location += nextLocation;
                    if (nextLocation != string::npos) { //checks to see if you are adding npos, NOT that the location after adding is npos because it will loop over from npos to a normal number
                        location += (size_t)5; //offsets what was already there
                        size_t nextEndChar = line.substr(location).find("\"");
                        if (nextEndChar != string::npos) {
                            if (line.substr(location, nextEndChar) != "Trn Premium") { //ensures that it is an actual hero
                                i++;
                                if (i % 2 == 0) { //only grabs every other alt text, otherwise will double up heros
                                    (*outputArray).push_back((line.substr(location, nextEndChar)));
                                    if ((1 - ((line.size() - (double)location) / line.size())) * 10 >= progressBarStatus) {
                                        cout << "#";
                                        progressBarStatus++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else {
                std::cout << "\n-------------------------------\nFound only 1 'Premium users don't see ads.'. Bad File Input\n-------------------------------\n";
                throw std::invalid_argument("Found only 1 'Premium users don't see ads.'. Bad File Input");
            }
        }
    }
}

int main()
{

    std::cout << "Program Start\n";
    vector<string> whitelist;
    whitelist.push_back("Grimm,End");
    whitelist.push_back("Eshawdow");
    whitelist.push_back("devilgriz");
    whitelist.push_back("LordThunderous");
    whitelist.push_back("osyl");

    Pixel graphPixel = Pixel(255,0,0);

    ImageCreator::fillImage(135,135,135);

    size_t numberOfPixels = ImageCreator::BmpInfoHeader().width * ImageCreator::BmpInfoHeader().height;
    //writes pixel data
    vector<Pixel> pixelArray;

    vector<Player> playerList;
    for (int i = 0; i < whitelist.size(); i++) { //initializes empty vector
        playerList.push_back(Player());
    }
    ifstream currentFile;
    for (int i = 0; i < whitelist.size(); i++) { //goes through each whitelisted player
        string username = whitelist.at(i);
        currentFile.open("PlayerData/" + username + "'s Marvel Rivals Match History - Marvel Rivals Tracker.html");
        playerList.at(i).name = username;
        std::cout << "\n---------- " << username << "----------\n";
        if (currentFile.is_open()) { //verify file
            findAttribute("Kills", &playerList.at(i).kills, &currentFile);
            currentFile.close();
            currentFile.open("PlayerData/" + username + "'s Marvel Rivals Match History - Marvel Rivals Tracker.html");
            findAttribute("Deaths", &playerList.at(i).deaths, &currentFile);
            currentFile.close();
            currentFile.open("PlayerData/" + username + "'s Marvel Rivals Match History - Marvel Rivals Tracker.html");
            findAttribute("Assists", &playerList.at(i).assists, &currentFile);
            currentFile.close();
            currentFile.open("PlayerData/" + username + "'s Marvel Rivals Match History - Marvel Rivals Tracker.html");
            findHeros(&playerList.at(i).heros, &currentFile);
            std::cout << "\nMatches Gathered from: " << playerList.at(i).kills.size() << "\n";
            std::cout << "\n";
        }
        else {
            std::cout << "Failed to get file\n";
        }
        currentFile.close();
    }
    //currentFile.close();
    std::cout << "Constructing Graphs...\n";
    ImageCreator::fillImage(135, 135, 135);
    drawGraph("Grimm,End kills", playerList.at(0).kills, graphPixel);
    ImageCreator::finishImage("normalGraph");
    std::cout << "   > normalGraph.bmp Constructed\n";
    ImageCreator::fillImage(135, 135, 135);
    drawAverageGraph("Grimm,End kill average", playerList.at(0).kills, graphPixel,true,-1,true,-1,false);
    ImageCreator::finishImage("averageGraph");
    std::cout << "   > averageGraph.bmp Constructed\n";
    ImageCreator::fillImage(135, 135, 135);
    drawAverageGraph("kill average", playerList.at(0).kills, graphPixel, 0, 30,true, -1, false, 25);
    drawAverageGraph("kill average", playerList.at(1).kills, Pixel(0,0,255), 0, 30, false,-1,false,25);
    drawAverageGraph("kill average", playerList.at(2).kills, Pixel(0, 255, 255), 0, 30, false, -1, false, 25);
    drawAverageGraph("kill average", playerList.at(3).kills, Pixel(255, 255, 0), 0, 30, false, -1, false, 25);
    drawAverageGraph("kill average", playerList.at(4).kills, Pixel(0, 255, 0), 0, 30, false, -1, false, 25);
    ImageCreator::finishImage("groupKillAverage");
    std::cout << "   > groupKillAverage.bmp Constructed\n";
    ImageCreator::fillImage(135, 135, 135);
    drawAverageGraph("death average", playerList.at(0).deaths, graphPixel, 0, 9, true, -1, false, 25);
    drawAverageGraph("death average", playerList.at(1).deaths, Pixel(0, 0, 255), 0, 9, false, -1, false, 25);
    drawAverageGraph("death average", playerList.at(2).deaths, Pixel(0, 255, 255), 0, 9, false, -1, false, 25);
    drawAverageGraph("death average", playerList.at(3).deaths, Pixel(255, 255, 0), 0, 9, false, -1, false, 25);
    drawAverageGraph("death average", playerList.at(4).deaths, Pixel(0, 255, 0), 0, 9, false, -1, false, 25);
    ImageCreator::finishImage("groupDeathAverage");
    std::cout << "   > groupDeathAverage.bmp Constructed\n";
    ImageCreator::fillImage(135, 135, 135);
    drawAverageGraph("assist average", playerList.at(0).assists, graphPixel, 0, 24, true, -1, false, 25);
    drawAverageGraph("assist average", playerList.at(1).assists, Pixel(0, 0, 255), 0, 24, false, -1, false, 25);
    drawAverageGraph("assist average", playerList.at(2).assists, Pixel(0, 255, 255), 0, 24, false, -1, false, 25);
    drawAverageGraph("assist average", playerList.at(3).assists, Pixel(255, 255, 0), 0, 24, false, -1, false, 25);
    drawAverageGraph("assist average", playerList.at(4).assists, Pixel(0, 255, 0), 0, 24, false, -1, false, 25);
    ImageCreator::finishImage("groupAssistAverage");
    std::cout << "   > groupAssistAverage.bmp Constructed\n";
    vector<vector<int>> combinedKills;
    combinedKills.push_back(playerList.at(0).kills);
    combinedKills.push_back(playerList.at(1).kills);
    combinedKills.push_back(playerList.at(2).kills);
    combinedKills.push_back(playerList.at(3).kills);
    combinedKills.push_back(playerList.at(4).kills);
    ImageCreator::fillImage(135, 135, 135);
    stackGraphs("stackedGraphs", combinedKills,-1,-1,25);
    ImageCreator::finishImage("stackedGraphs");
    std::cout << "   > stackedGraphs.bmp Constructed\n";
    system("stackedGraphs.bmp");
    //system("normalGraph.bmp");
    //system("averageGraph.bmp");
    //system("forceScaledGraph.bmp");
    system("groupKillAverage.bmp");
}
