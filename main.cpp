//
//  main.cpp
//  CS 31 Project 3
//
//  Created by Guoran Ye on 5/4/18.
//  Copyright © 2018 Guoran Ye. All rights reserved.
//

#include <iostream>
using namespace std;

bool hasCorrectSyntax(string song)
{
    int i;
    if (song == ""){
        return true;
    }
    else{
        i = 0;
        while (i < song.length()){
            if (song[i] == 'G'||song[i] == 'g'||song[i] == 'R'||song[i] == 'r'||song[i] == 'Y'||song[i] == 'y'||song[i] == 'B'||song[i] == 'b'||song[i] == 'O'||song[i] == 'o'){
                if (song[i+1] == '0'||song[i+1] == '1'||song[i+1] == '2'||song[i+1] == '3'||song[i+1] == '4'||song[i+1] == '5'||song[i+1] == '6'||song[i+1] == '7'||song[i+1] == '8'||song[i+1] == '9'){
                    if (song[i+2] == '0'||song[i+2] == '1'||song[i+2] == '2'||song[i+2] == '3'||song[i+2] == '4'||song[i+2] == '5'||song[i+2] == '6'||song[i+2] == '7'||song[i+2] == '8'||song[i+2] == '9'){
                        if (song[i+3] == '/'){
                            i = i + 4;
                        }
                        else{
                            break;
                        }
                    }
                    else if (song[i+2] == '/'){
                        i = i + 3;
                    }
                    else{
                        break;
                    }
                }
                else if (song[i+1] == '/'){
                    i = i + 2;
                }
                else{
                    break;
                }
            }
            else if (song[i] == '/'){
                i = i + 1;
            }
            else{
                break;
            }
        }
        if (i == song.length()){
            return true;
        }
        else{
            return false;
        }
    }
}

int translateSong(string song, string& instructions, int& badBeat)
{
    int beat = 1;
    int i = 0;
    string currentInstructions = "";
    if (!hasCorrectSyntax(song)){
        return 1;
    }
    else if (song == ""){
        instructions = "";
        return 0;
    }
    else{
        while (i < song.length()){
            if (song[i] == '/'){
                currentInstructions += "x";
                i ++;
                beat ++;
            } //if the first char is '/', print x, move to the next char and restart the process
            else{ //if the first is a letter
                if (song[i+1] == '/'){
                    currentInstructions += tolower(song[i]);
                    i += 2;
                    beat ++;
                } //if the second is '/', print the letter in lower case, move to the next char and restart the process
                else{//if the second is a digit
                    if (song[i+2] == '/'){//if the third is '/'
                        if (song[i+1] == '0' || song[i+1] == '1'){ //if the digit is 0 or 1
                            badBeat = beat;
                            return 2;
                            break;//end process. set badBeat and return 2.
                        }
                        else{
                            int j = 2;
                            while (j <= song[i+1] - 47 && j+i+1 <= song.length()){
                                if (song[i+j] == '/'){
                                    j++;
                                    beat++;
                                }
                                else{
                                    badBeat = beat;
                                    return 3;
                                    break;
                                    break;
                                }
                            }
                            if (j <= song[i+1] - 47){
                                badBeat = beat;
                                return 4;
                                break;
                            }
                            else{
                                int k = 1;
                                while(k <= song[i+1] - 48){
                                    currentInstructions += toupper(song[i]);
                                    k++;
                                }
                                i = i + song[i+1] - 46;
                                beat ++;
                            }
                        }
                    }
                    else{
                        if (song[i+1]-48 == 0 && (song[i+2]-48 == 0 || song[i+2]-48 == 1)){
                            badBeat = beat;
                            return 2;
                            break;
                        }
                        else{
                            int j = 3;
                            while (j <= (song[i+1] - 48)*10 + song[i+2] - 46 && j+i+1 <= song.length()){
                                if (song[i+j] == '/'){
                                    j++;
                                    beat++;
                                }
                                else{
                                    badBeat = beat;
                                    return 3;
                                    break;
                                    break;
                                }
                            }
                            if (j <= (song[i+1] - 48)*10 + song[i+2] - 46){
                                badBeat = beat;
                                return 4;
                                break;
                            }
                            else{
                                int k = 1;
                                while(k <= ((song[i+1] - 48)*10 + song[i+2] - 48)){
                                    currentInstructions += toupper(song[i]);
                                    k++;
                                }
                                i = i + (song[i+1] - 48)*10 + song[i+2] - 45;
                                beat++;
                            }
                        }
                    }
                }
            }
        }
        instructions = currentInstructions;
        return 0;
    }
}

int main()
{
    string song;
    string instruct = "wrong";
    int badb = -99;
    cout << "Enter song: ";
        getline(cin, song);
    translateSong(song, instruct, badb);
    cout << "situation: " << translateSong(song, instruct, badb) << endl;
    cout << "instructions: " << instruct << endl;
    cout << "bad beat: " << badb << endl;
}


