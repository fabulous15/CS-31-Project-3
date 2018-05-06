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
    
}

int main()
{
    string song;
    cout << "Enter song: ";
        getline(cin, song);
    if (hasCorrectSyntax(song))
        cout << "good";
    else
        cout << "bad";
}


