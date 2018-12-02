#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;
const int MAX_WORD_LENGTH = 20;

int makeProper(char word1[][MAX_WORD_LENGTH + 1],
	char word2[][MAX_WORD_LENGTH + 1],
	int separation[],
	int nPatterns);
int rate(const char document[],
	const char word1[][MAX_WORD_LENGTH + 1],
	const char word2[][MAX_WORD_LENGTH + 1],
	const int separation[],
	int nPatterns);
int main()
{
	
}
//works ;_; with empty strings, non-alphabetical, and negative separation 
//every while loop is the result of me forgetting the existence of strcmp. 
//they're all exactly the same (with relevant inputs), but they are the same 
int makeProper(char word1[][MAX_WORD_LENGTH + 1],
	char word2[][MAX_WORD_LENGTH + 1],
	int separation[],
	int nPatterns) {
	//sets separation[i] = -1 for each invalid pattern from an empty cstring or negative separation 
	//that is, a -1 as the separation value is a flag that the pattern at that index is somehow invalid. 
	for (int i = 0; i < nPatterns; i++) {
		int index = 0;
		bool validPattern = true;
		//iterates thru word1 and makes sure uppercases are converted to lowercases 
		while (word1[i][index] != '\0') {
			if (isupper(word1[i][index]) != 0) {
				word1[i][index] = tolower(word1[i][index]);
			}
			//if it's not alphabetical, it returns 0 or false
			if (isalpha(word1[i][index]) == false) {
				validPattern = false;
			}
			index++;
		}
		//if index is never incremented, the cstring is empty so it's invalid 
		if (index == 0) {
			validPattern = false;
		}
		index = 0;
		//makes sure all things in word2 are lowercase
		while (word2[i][index] != '\0') {
			if (isupper(word2[i][index]) != 0) {
				word2[i][index] = tolower(word2[i][index]);
			}
			if (isalpha(word2[i][index]) == false) {
				validPattern = false;
			}
			index++;
		}
		//if index is never incremented, the cstring is empty so it's invalid 
		if (index == 0) {
			validPattern = false;
		}
		//every invalid pattern will have -1 at separation[i] for easy reference 
		if (validPattern == false) {
			separation[i] = -1;
		}
		//helper message to the debugger 
		if (separation[i] < 0) {
			separation[i] = -1;
		}
		else {
		}
	}
	//now, start checking for duplicates
	for (int i = 0; i < nPatterns - 1; i++) {
		for (int j = i + 1; j < nPatterns; j++) {
			int index = 0;
			bool firstSame = false;
			bool secondSame = false;
			//while word1 at some index is the same as word1 at another index, index increments
			//so if index increments to the length of the word, then they must be the same string.
			//therefore it sets firstSame to true
			while (word1[i][index] == word1[j][index] && word1[i][index] != '\0') {
				index++;
			}
			if (index == strlen(word1[i])) {
				firstSame = true;
			}
			index = 0;
			//now if both in word1 and word2 the words are the same, it sets secondSame to true
			while (word2[i][index] == word2[j][index] && word2[i][index] != '\0') {
				index++;
			}
			if (index == strlen(word2[i])) {
				secondSame = true;
			}
			//if BOTH firstSame and secondSame are true, then they're the same! So the one with the lower separation value must be eliminated. 
			if (firstSame == true && secondSame == true) {
				if (separation[i] > separation[j]) {
					separation[j] = -1;
				}
				else {
					separation[i] = -1;
				}
			}
			//now, to check for if w1 and w2 are the same ;_;
			firstSame = false;
			secondSame = false;
			while (word1[i][index] == word2[j][index] && word1[i][index] != '\0' && word2[j][index] != '\0') {
				index++;
			}
			//only if the w1 and w2 are the same do we check the other ones 
			if (index == strlen(word1[i]) && index == strlen(word2[j])) {
				firstSame = true;
				index = 0;
				//checks the pairs of the w1 and w2 to see if they're also the same 
				while (word2[i][index] == word1[j][index] && word1[j][index] != '\0' && word2[i][index] != '\0') {
					index++;
				}
				//if they're both the exact same string, this should work! :)
				//if one of them is the same+some more letters, this also checks for that because it uses strlen 
				if (index == strlen(word2[i]) && index == strlen(word1[j])) {
					if (separation[i] > separation[j]) {
						separation[j] = -1;
					}
					else {
						separation[i] = -1;
					}
				}
			}
		}
	}
	//for every pattern where separation[i] is -1, it must be invalid (as determined earlier). Therefore, it gets swapped to the back. 
	//i.e if it's invalid, it's put to the end of each array. 
	for (int i = 0; i < nPatterns - 1; i++) {
		for (int j = i + 1; j < nPatterns; j++) {
			if (separation[i] == -1) {
				//swap word1, keeping null character at the end
				for (int k = 0; k < 20; k++) {
					swap(word1[i][k], word1[j][k]);
				}
				//swap word2, keeping null character at the end
				for (int k = 0; k < 20; k++) {
					swap(word2[i][k], word2[j][k]);
				}
				//swap sep
				int temp = separation[i];
				separation[i] = separation[j];
				separation[j] = temp;
			}
		}
	}
	int numProper = 0;
	//reads out the words to make sure nothing gets screwed up 
	for (int i = 0; i < nPatterns; i++) {
		
		if (!(separation[i] < 0)) {
			numProper++;
		}
	}
	//returns the # of proper patterns with the arrays sorted. Invalid patterns are at the end. 
	return numProper;
}
//copies all of document into a new cstring called myDoc
void copy(const char document[], char myDoc[]) {
	int index = 0;
	for (int i = 0; i < strlen(document); i++) {
		if (isalpha(document[i])) {
			if (isupper(document[i])) {
				myDoc[index] = tolower(document[i]);
				index++;
			}
			else {
				myDoc[index] = document[i];
				index++;
			}
		}
		//if it's a space, it also gets added to myDoc. 
		else if (document[i] == ' ' && i != 0) {
			myDoc[index] = ' ';
			index++;
		}
	}
	myDoc[index] = '\0';
}
//separates myDoc into an array of cStrings 
int intoCStrings(char myDoc[], char myWords[][25]) {
	int numWords = 0;
	int indWord = 0;
	for (int i = 0; i < strlen(myDoc); i++) {
		//goes to the next index if there's a space 
		//non alphabetical characters were already eliminated, so this is easy :) 
		if (myDoc[i] == ' ') {
			numWords++;
			myWords[numWords][indWord] = '\0';
			indWord = 0;
		}
		else {
			//words cannot be over 20 characters long, so if it's more, end the cstring with a NUL character
			if (indWord < 21 && isalpha(myDoc[i])) {
				myWords[numWords][indWord] = myDoc[i];
			}
			else {
				myWords[numWords][20] = '\0';
				indWord = 20;
			}
			indWord++;
		}
		//makes sure there are no out-of-bounds errors
		if (indWord > 20) {
			indWord = 20;
		}
	}
	return numWords;
}
int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns) {
	int rating = 0;
	int index = 0;
	char myDoc[251] = "";
	//like strcpy, but prevents extra bits :) 
	copy(document, myDoc);
	char myWords[255][25] = {'\0'};
	int numWords = intoCStrings(myDoc, myWords);
	//now with it separated into words, we can compare. 
	//checks every pattern 
	for (int k = 0; k < nPatterns; k++) {
		bool isPattern = false;
		for (int i = 0; i < numWords + 1; i++) {
			//finds the w1 in the pattern
			if (strcmp(myWords[i], word1[k]) == 0) {
				int spacing = 0;
				//finds a w2 matching that w1, and if it's found, break out into increasing the rating
				for (int j = i + 1; j < numWords+1; j++) {
					if (strcmp(myWords[j], word2[k])==0) {
						if (spacing <= separation[k]) {
							isPattern = true;
						}
						break;
					}
					//if they aren't the same, there must be another word in between 
					else {
						spacing++;
					}
				}
				spacing = 0;
				//if it's a pattern, there's no need to check for another instance of the same pattern 
				if (isPattern) {
					break;
				}
				//the same thing, but backwards
				for (int j = i -1; j > -1; j--) {
					if (strcmp(myWords[j], word2[k]) == 0) {
						if (spacing <= separation[k]) {
							isPattern = true;
						}
						break;
					}
					else {
						spacing++;
					}
				}
				if (isPattern) {
					break;
				}
			}
		}
		//only increments if there is a pattern from the breaks
		if (isPattern) {
			rating++;
		}
	}
	return rating;
}