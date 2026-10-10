#pragma once
#include <iostream>
#include <string>
namespace ascii {
	static std::string Char(char character,bool* success) {
        string characterData;
        *success = true;
        if (character == 'a') {
            characterData = "_###_";
            characterData += "#___#";
            characterData += "#####";
            characterData += "#___#";
            characterData += "#___#";
        }
        else if (character == 'b') {
            characterData = "####_";
            characterData += "#___#";
            characterData += "####_";
            characterData += "#___#";
            characterData += "####_";
        }
        else if (character == 'c') {
            characterData = "#####";
            characterData += "#____";
            characterData += "#____";
            characterData += "#____";
            characterData += "#####";
        }
        else if (character == 'd') {
            characterData = "####_";
            characterData += "#___#";
            characterData += "#___#";
            characterData += "#___#";
            characterData += "####_";
        }
        else if (character == 'e') {
            characterData = "#####";
            characterData += "#____";
            characterData += "#####";
            characterData += "#____";
            characterData += "#####";
        }
        else if (character == 'f') {
            characterData = "#####";
            characterData += "#____";
            characterData += "#####";
            characterData += "#____";
            characterData += "#____";
        }
        else if (character == 'g') {
            characterData = "#####";
            characterData += "#____";
            characterData += "#__##";
            characterData += "#___#";
            characterData += "#####";
        }
        else if (character == 'h') {
            characterData = "#___#";
            characterData += "#___#";
            characterData += "#####";
            characterData += "#___#";
            characterData += "#___#";
        }
        else if (character == 'i') {
            characterData = "#####";
            characterData += "__#__";
            characterData += "__#__";
            characterData += "__#__";
            characterData += "#####";
        }
        else if (character == 'j') {
            characterData = "#####";
            characterData += "____#";
            characterData += "____#";
            characterData += "#___#";
            characterData += "_###_";
        }
        else if (character == 'k') {
            characterData = "#___#";
            characterData += "#__#_";
            characterData += "###__";
            characterData += "#__#_";
            characterData += "#___#";
        }
        else if (character == 'l') {
            characterData = "#____";
            characterData += "#____";
            characterData += "#____";
            characterData += "#____";
            characterData += "#####";
        }
        else if (character == 'm') {
            characterData = "#___#";
            characterData += "##_##";
            characterData += "#_#_#";
            characterData += "#___#";
            characterData += "#___#";
        }
        else if (character == 'n') {
            characterData = "#___#";
            characterData += "##__#";
            characterData += "#_#_#";
            characterData += "#__##";
            characterData += "#___#";
        }
        else if (character == 'o') {
            characterData = "_###_";
            characterData += "#___#";
            characterData += "#___#";
            characterData += "#___#";
            characterData += "_###_";
        }
        else if (character == 'p') {
            characterData = "#####";
            characterData += "#___#";
            characterData += "#####";
            characterData += "#____";
            characterData += "#____";
        }
        else if (character == 'q') {
            characterData = "_###_";
            characterData += "#___#";
            characterData += "#___#";
            characterData += "#__#_";
            characterData += "_##_#";
        }
        else if (character == 'r') {
            characterData = "####_";
            characterData += "#___#";
            characterData += "####_";
            characterData += "#___#";
            characterData += "#___#";
        }
        else if (character == 's') {
            characterData = "#####";
            characterData += "#____";
            characterData += "#####";
            characterData += "____#";
            characterData += "#####";
        }
        else if (character == 't') {
            characterData = "#####";
            characterData += "__#__";
            characterData += "__#__";
            characterData += "__#__";
            characterData += "__#__";
        }
        else if (character == 'u') {
            characterData = "#___#";
            characterData += "#___#";
            characterData += "#___#";
            characterData += "#___#";
            characterData += "_###_";
        }
        else if (character == 'v') {
            characterData = "#___#";
            characterData += "#___#";
            characterData += "_#_#_";
            characterData += "_#_#_";
            characterData += "__#__";
        }
        else if (character == 'w') {
            characterData = "#_#_#";
            characterData += "#_#_#";
            characterData += "#_#_#";
            characterData += "##_##";
            characterData += "#___#";
        }
        else if (character == 'x') {
            characterData = "#___#";
            characterData += "#___#";
            characterData += "_###_";
            characterData += "#___#";
            characterData += "#___#";
        }
        else if (character == 'y') {
            characterData = "#___#";
            characterData += "#___#";
            characterData += "_#_#_";
            characterData += "__#__";
            characterData += "__#__";
        }
        else if (character == 'z') {
            characterData = "#####";
            characterData += "___#_";
            characterData += "_#___";
            characterData += "#____";
            characterData += "#####";
        }
        else if (character == '1') {
            characterData = "###__";
            characterData += "__#__";
            characterData += "__#__";
            characterData += "__#__";
            characterData += "#####";
        }
        else if (character == '2') {
            characterData = "#####";
            characterData += "____#";
            characterData += "#####";
            characterData += "#____";
            characterData += "#####";
        }
        else if (character == '3') {
            characterData = "#####";
            characterData += "____#";
            characterData += "#####";
            characterData += "____#";
            characterData += "#####";
        }
        else if (character == '4') {
            characterData = "#___#";
            characterData += "#___#";
            characterData += "#####";
            characterData += "____#";
            characterData += "____#";
        }
        else if (character == '5') {
            characterData = "#####";
            characterData += "#____";
            characterData += "#####";
            characterData += "____#";
            characterData += "#####";
        }
        else if (character == '6') {
            characterData = "#####";
            characterData += "#____";
            characterData += "#####";
            characterData += "#___#";
            characterData += "#####";
        }
        else if (character == '7') {
            characterData = "#####";
            characterData += "____#";
            characterData += "____#";
            characterData += "____#";
            characterData += "____#";
        }
        else if (character == '8') {
            characterData = "#####";
            characterData += "#___#";
            characterData += "#####";
            characterData += "#___#";
            characterData += "#####";
        }
        else if (character == '9') {
            characterData = "#####";
            characterData += "#___#";
            characterData += "#####";
            characterData += "____#";
            characterData += "#####";
        }
        else if (character == '0') {
            characterData = "#####";
            characterData += "#___#";
            characterData += "#___#";
            characterData += "#___#";
            characterData += "#####";
        }
        else if (character == ' ') {
            characterData = "_____";
            characterData += "_____";
            characterData += "_____";
            characterData += "_____";
            characterData += "_____";
        }
        else if (character == '.') {
            characterData = "_____";
            characterData += "_____";
            characterData += "_____";
            characterData += "_____";
            characterData += "__#__";
        }
        else if (character == ',') {
            characterData = "_____";
            characterData += "_____";
            characterData += "_____";
            characterData += "__#__";
            characterData += "__#__";
            }
        else {
            characterData = "#####";
            characterData += "#####";
            characterData += "#####";
            characterData += "#####";
            characterData += "#####";
            *success = false;
        }
        return characterData;
	}
	
}