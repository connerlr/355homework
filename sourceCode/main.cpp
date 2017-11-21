#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<algorithm>

using namespace std;

int main() {

	ifstream myReadFile;
	string filename, buffer;
	string numOfStates, acceptingState;
	cout << "Please input the file name you wish to search\n";
	cin >> filename;
	myReadFile.open(filename.c_str());
	char output[100];
	int alphabetLength;
	if (myReadFile.is_open()) 
	{
		char findInt[100];

		//Get number of states
		getline(myReadFile,buffer);
		for(int i = 0; i < buffer.size(); i++)
		{
			findInt[i] = buffer[i];
		}
		for(int i = 0; i < strlen(findInt); i++)
		{
			if(isdigit(findInt[i]))
			{
				numOfStates = findInt[i];
			}
		}
		int numInt = stoi(numOfStates); //number of states as an Integer
		//Get accepting state
		//TODO get all of the states instead of the one
		getline(myReadFile,buffer);
		for(int i = 0; i < buffer.size(); i++)
		{
			findInt[i] = buffer[i];
		}
		for(int i = 0; i < strlen(findInt); i++)
		{
			if(isdigit(findInt[i]))
			{
				acceptingState = findInt[i];
			}
		}
		int numState = stoi(acceptingState);//accepting state needs to be array
		//Get the alphabet as an Array
		getline(myReadFile,buffer);
		buffer.erase(0,10);
		int alphaLength = buffer.length();//number of choices in alphabet


		int dfaTable[numInt][alphaLength];//DFA table as a 2d array


		char alphabet[alphaLength]; //alphabet as char array
		cout << "\n" << "\n";
		cout << "Num of states is this: " << numInt << "\n";
		cout << "The accepting state is " << numState << "\n";
		for(int i = 0; i < buffer.length(); i++)
		{
			alphabet[i] = buffer[i];
			cout << alphabet[i];
		}
		cout << "\n";
		for(int i = 0; i < numInt; i++)
		{
			getline(myReadFile,buffer);
			buffer.erase(remove(buffer.begin(), buffer.end(), ' '),buffer.end());	
			cout << buffer << "\n";
		}
	}
	cout << "\n";
	myReadFile.close();
	return 0;
}

