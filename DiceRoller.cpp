/* 
Written by: Nicholas Cockcroft
Date: July 25, 2018

Description: Write a program to take in the number of rolls and the number of sides of dies in the format #d#.
For more details, see the original reddit post:
https://stackoverflow.com/questions/9246536/warning-c4244-argument-conversion-from-time-t-to-unsigned-int-possible

*/
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // G0enertae random numbers
#include <ctime> // Seeding random numbers with time
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

bool ValidInput(string dice);
bool IsDigits(string &num);
int getRolls(string &dice);
int getSides(string &dice);
void CalculateRolls(int rolls, int sideOfDie);

int main() {

	// Seeding the rng with time
	srand((unsigned int)time(0));

	// Initial variables
	string diceInput;
	vector <string> dices;

	cout << "Enter the number of dice and number of sides (Ex: \"4d5\"). " << endl;
	cout << "Enter \"0\" to stop: " << endl;

	while (diceInput != "0") {

		cout << "Input: ";
		cin >> diceInput;

		// Checking to ensure the user followed the format with #d#
		if (!ValidInput(diceInput) && diceInput != "0") {
			cout << "Error: Invalid string of input. Skipping entry" << endl;
			continue;
		}

		if (diceInput != "0") {
			dices.push_back(diceInput);
		}
	}

	// For all of the dices that the user typed in, calculate random rolls for them
	for (size_t i = 0; i < dices.size(); i++) {
		CalculateRolls(getRolls(dices[i]), getSides(dices[i]));
	}

	system("pause");
	return 0;
}

// Function for checking if the user entered a string in the format #d#. Returns true if they did, returns false if they didnt.
bool ValidInput(string dice) {

	stringstream ss(dice);
	string token;
	int count = 0;
	bool isValid = true;

	while (getline(ss, token, 'd')) {
		try {
			if (stoi(token) < 0 || stoi(token) > 100 || !IsDigits(token)) {
				isValid = false;
			}
		}
		catch (exception e) {
			isValid = false;
		}

		if (count > 1) {
			isValid = false;
		}
		count++;
	}

	if (count == 1) {
		isValid = false;
	}
	return isValid;
}

// Checks if a string that is passed into it is a number of not.
bool IsDigits(string &num) {
	return all_of(num.begin(), num.end(), ::isdigit);
}

// Gets the number of rolls from the string format #d#.
int getRolls(string &dice) {
	stringstream ss(dice);
	string token;
	int rolls;

	getline(ss, token, 'd');
	rolls = stoi(token);
	return rolls;
}

// Gets the number of sides of a die from the string format #d#.
int getSides(string &dice) {
	stringstream ss(dice);
	string token;
	int sides;

	getline(ss, token, 'd');
	getline(ss, token, 'd');
	sides = stoi(token);
	cout << "This is sides: " << sides << endl;

	return sides;

}

// Calculates the rolls by taking in the number of rolls and the number of sides of a dice and randomly generates a "roll" to be added up and printed for the user.
void CalculateRolls(int rolls, int sideOfDie) {
	int totalNum = 0;

	for (int i = 0; i < rolls; i++) {
		totalNum += rand() % sideOfDie;
	}

	cout << "Output: " << totalNum << endl;
}