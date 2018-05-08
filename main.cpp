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
            if (song[i] == 'G'||song[i] == 'g'||song[i] == 'R'||song[i] == 'r'||song[i] == 'Y'||song[i] == 'y'||song[i] == 'B'||song[i] == 'b'||song[i] == 'O'||song[i] == 'o'){ //check if the first character of the beat is a color
                if (song[i+1] == '0'||song[i+1] == '1'||song[i+1] == '2'||song[i+1] == '3'||song[i+1] == '4'||song[i+1] == '5'||song[i+1] == '6'||song[i+1] == '7'||song[i+1] == '8'||song[i+1] == '9'){ //check if the second character of the beat is a digit
                    if (song[i+2] == '0'||song[i+2] == '1'||song[i+2] == '2'||song[i+2] == '3'||song[i+2] == '4'||song[i+2] == '5'||song[i+2] == '6'||song[i+2] == '7'||song[i+2] == '8'||song[i+2] == '9'){ //check if the third character of the beat is a digit
                        if (song[i+3] == '/'){
                            i += 4; //move to the next beat
                        }
                        else{
                            break;
                        }
                    }
                    else if (song[i+2] == '/'){
                        i += 3; //move to the next beat
                    }
                    else{
                        break;
                    }
                }
                else if (song[i+1] == '/'){
                    i += 2; //move to the next beat
                }
                else{
                    break;
                }
            }
            else if (song[i] == '/'){
                i ++; //move to the next beat
            }
            else{
                break;
            }
        }
        if (i == song.length()){ //if the checking process ends after finish checking the last character
            return true;
        }
        else{
            return false; //if the checking process ends before finish checking the last character
        }
    }
}

int translateSong(string song, string& instructions, int& badBeat)
{
    int beat = 1;
    int i = 0;
    string currentInstructions = "";
    if (!hasCorrectSyntax(song)){ //for all songs without correct syntax
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
                i ++; //move to the next beat
                beat ++; //update the beat we are checking
            } //if the first character is '/', print x, move to the next character and restart the checking process
            else{ //if the first is a letter
                if (song[i+1] == '/'){
                    currentInstructions += tolower(song[i]);
                    i += 2; //move to the next beat
                    beat ++; //update the beat we are checking
                } //if the second is '/', print the letter in lower case, move to the next character and restart the checking process
                else{ //if the second is a digit
                    if (song[i+2] == '/'){
                        if (song[i+1] == '0' || song[i+1] == '1'){ //if the digit is 0 or 1
                            badBeat = beat;
                            return 2;
                            break;
                        }
                        else{ //if the digit is at least 2
                            int j = 2;
                            while (j <= song[i+1] - 47 && j+i+1 <= song.length()){ //check if right number of slashes follows the digit without running out of the length of the song
                                if (song[i+j] == '/'){
                                    j++; //move to the next beat
                                    beat++; //update the beat we are checking
                                }
                                else{ //if we meet a non-slash character
                                    badBeat = beat;
                                    return 3;
                                    break;
                                    break;
                                }
                            }
                            if (j <= song[i+1] - 47){ //if the song ends prematurely
                                badBeat = beat;
                                return 4;
                                break;
                            }
                            else{ //if the number of slashes follows the digit is correct
                                int k = 1;
                                while(k <= song[i+1] - 48){
                                    currentInstructions += toupper(song[i]);
                                    k++;
                                } // add the right number of upper-case letters to the temporary instructions
                                i = i + song[i+1] - 46; //move to the next beat
                            }
                        }
                    }
                    else{ //if the third character is a digit
                        if (song[i+1]-48 == 0 && (song[i+2]-48 == 0 || song[i+2]-48 == 1)){ //if the two digit constitute 00 or 01
                            badBeat = beat;
                            return 2;
                            break;
                        }
                        else{ //if the number formed by the two digits is at least 2
                            int j = 3;
                            while (j <= (song[i+1] - 48)*10 + song[i+2] - 46 && j+i+1 <= song.length()){  //check if right number of slashes follows the digit without running out of the length of the song
                                if (song[i+j] == '/'){
                                    j++; //move to the next beat
                                    beat++; //update the beat we are checking
                                }
                                else{ //if we meet a non-slash character
                                    badBeat = beat;
                                    return 3;
                                    break;
                                    break;
                                }
                            }
                            if (j <= (song[i+1] - 48)*10 + song[i+2] - 46){ //if the song ends prematurely
                                badBeat = beat;
                                return 4;
                                break;
                            }
                            else{ //if the number of slashes follows the digit is correct
                                int k = 1;
                                while(k <= ((song[i+1] - 48)*10 + song[i+2] - 48)){
                                    currentInstructions += toupper(song[i]);
                                    k++;
                                } // add the right number of upper-case letters to the temporary instructions
                                i = i + (song[i+1] - 48)*10 + song[i+2] - 45; //move to the next beat
                            }
                        }
                    }
                }
            }
        }
        instructions = currentInstructions; //set instructions as the temporary instructions if nothing went wrong thoughout the whole cheking process
        return 0;
    }
}

int main()
{
    string song;
    string instruct = "The song is not translatable.";
    int badb = -99;
    cout << "Enter song: ";
        getline(cin, song);
    translateSong(song, instruct, badb);
    cout << "Instructions: " << instruct << endl;
    cout << "Situation: " << translateSong(song, instruct, badb) << endl;
    cout << "Bad beat: " << badb << endl;
}
