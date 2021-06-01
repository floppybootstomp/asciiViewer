#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <conio.h>
#include <Windows.h>

using namespace std;

// draw ascii art unmodified by color pallet
// inputs: filename
void drawAsciiWhite(string afp){
	system("cls");
	cout << "file: " << afp << endl; // print out the filename
	
	// print the file data
	string word;
	fstream aStream;
	aStream.open(afp);
	if(aStream.is_open()){
		while(getline(aStream, word)){
			for(int i = 0; i < word.size(); i ++){
				cout << word[i] << " ";
			}
			cout << endl;
		}
	}
	else{ // error opening file (file never opened)
		cout << "errorzors! sorry!" << endl;
	}
	
}

// draw ascii art with color pallet modification
// inputs: filename, color pallet, whether to colorize the background or not, coloration mode
void drawAsciiFill(string afp, unordered_map<char, int> cPal, int block, int numColors){
	system("cls");
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int col = 15;
	FlushConsoleInputBuffer(hConsole);
	
	string word;
	fstream aStream;
	aStream.open(afp);
	if(aStream.is_open()){
		while(getline(aStream, word)){
			for(int i = 0; i < word.size(); i ++){
				switch(numColors){
					case 0: // mode 2: supress all colors except for black and colorless
						if(cPal.find(word[i]) != cPal.end() && cPal[word[i]] == 0) // color black
							col = 15 + block*16*15;
						else if(cPal.find(word[i]) == cPal.end()) // color colorless
							col = 15;
						else // suppress colors
							col = 0;
						SetConsoleTextAttribute(hConsole, (col));
						cout << word[i] << " ";
					break;
					case 1: // mode 3: supress all colors except for black, white, grey (7), grey (8), and colorless. set colorless to grey(8)
						if(cPal.find(word[i]) != cPal.end() && cPal[word[i]] == 7 || cPal[word[i]] == 8 || cPal[word[i]] == 15) // color grey and white
							col = cPal[word[i]] + block*16*cPal[word[i]]; 
						else if(cPal.find(word[i]) != cPal.end() && cPal[word[i]] == 0) // color black
							col = 8 + block*16*8; 
						else if(cPal.find(word[i]) == cPal.end()) // color colorless
							col = 15;
						else // supress colors
							col = 0;
						SetConsoleTextAttribute(hConsole, (col));
						cout << word[i] << " ";
					break;
					case 2: // mode 4, 5: show all colors (mode 4: replace spaces with '.'; mode 5: color background)
						if(cPal.find(word[i]) != cPal.end()) // color all colors specified
							col = cPal[word[i]] + block*16*cPal[word[i]]; 
						else if(cPal.find(' ') != cPal.end()) // color spaces
							col = cPal[' '] + block*16*cPal[' '];
						else // color unspecified characters
							col = 0;
						if(block == 0 && col == 0) // recolor to dark grey if the color is black and the background isn't drawn
							col = 8;
						if(block == 0 && word[i] == ' '){ // replace spaces with '.'
							word[i] = '.';
						}
						SetConsoleTextAttribute(hConsole, (col));
						cout << word[i] << " ";
					break;
				}
			}
			cout << endl;
		}
	}
	else{ // error opening file (file never opened)
		cout << "errorzors! sorry!" << endl;
	}
	// reset the console color scheme back to 15 (default black background with white text)
	SetConsoleTextAttribute(hConsole, 15);
	
}

// cycle through possible colors 0 to 15 and print them out
void drawColorReference(){
	system("cls");
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int col = 15;
	FlushConsoleInputBuffer(hConsole);
	for(int i = 0; i < 16; i ++){
		SetConsoleTextAttribute(hConsole, i);
		cout << i << endl;
	}
	// reset the console color scheme back to 15 (default black background with white text)
	SetConsoleTextAttribute(hConsole, 15);
}

int main(){
	// user inputs files...
	string finput;
	cout << "ascii file path: ";
	cin >> finput;
	string asciiFilePath = finput;
	cout << "pallet file path: ";
	cin >> finput;
	string palletFilePath = finput;
	
	// create unordered map to store pallet information
	string word;
	unordered_map<char, int> cPallet;
	fstream palletStream;
	palletStream.open(palletFilePath);
	while(getline(palletStream, word)){
		cPallet[word.front()] = stoi(word.substr(2));
	}
	
	// allow user to cycle through coloration modes and print accordingly
	char input;
	while(input != 'q'){
		input = getch();
		switch(input){
			case '1': // mode 1: show ascii art unchanged by color pallet
				drawAsciiWhite(asciiFilePath);
				cout << asciiFilePath << endl;
			break;
			case '2': // mode 2: supress all colors except for black and colorless
				drawAsciiFill(asciiFilePath, cPallet, 0, 0);
			break;
			case '3': // mode 3: supress all colors except for black, white, grey (7), grey (8), and colorless. set colorless to grey(8)
				drawAsciiFill(asciiFilePath, cPallet, 0, 1);
			break;
			case '4': // mode 4: show all colors, replace spaces with '.'
				drawAsciiFill(asciiFilePath, cPallet, 0, 2);
			break;
			case '5': // mode 5: show all colors, mode 5: color background
				drawAsciiFill(asciiFilePath, cPallet, 1, 2);
			break;
			case '6': // draw color reference
				drawColorReference();
			break;
		}
	}
	system("cls");
	
	return 0;
}
