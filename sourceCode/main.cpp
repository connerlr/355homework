#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<algorithm>
#include<vector>

using namespace std;

int toAlphaNum(char str)
{
	if(isdigit(str))
	{
		string convert = "";
		convert += str;
		int toReturn = stoi(convert);
		return str;
	}

	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	for(int i = 0; i < alphabet.length(); i++)
	{
		if(str == alphabet[i])
		{
			return i + 10;

		}
	}
	
	return -1;
}

void testDFA(string str, vector<vector<int>> dfaTable, vector<int> acceptingSt, 
			 string alphabet)
{
	int currentState = 0;
	int goToState = 0;
	int dfaX;
	for(int i = 0; i < str.length(); i++)
	{
		for(int j = 0; j < alphabet.length(); j++)
		{
			if(alphabet[j] == str[i])
			{
				goToState = dfaTable[currentState][j];
			}
		}
		if(goToState != currentState)
		{
			for(int j = 0; j < alphabet.length(); j++)
			{
				if(alphabet[j] == str[i])
				{
					currentState = dfaTable[currentState][j];
				}
			}	
		}		
		
	}	
 	bool printed = false;
	for(int i = 0; i < acceptingSt.size(); i++)
	{
		if(currentState == acceptingSt[i])
		{
			printed = true;
			cout << "accept" << endl;
		}
	}
	if(printed == false)
		cout << "reject" << endl;
}

int main(int argc, char* argv[]) {

	ifstream myReadFile;
	string filename, filename2, buffer;
	string numOfStates;
	filename = argv[1];
	myReadFile.open(filename.c_str());
	int alphabetLength;
	if (myReadFile.is_open()) 
	{
		//Get number of states
		getline(myReadFile,buffer);
		for(int i = 0; i < buffer.length(); i++)
		{
			if(isdigit(buffer[i]))
			{
				numOfStates = numOfStates + buffer[i];
			}
		}
		int numInt = stoi(numOfStates); //number of states as an Integer
		

////////////////////////////////////////////////////////////////////////////////

		//Get accepting states
		getline(myReadFile,buffer);
		buffer.erase(0,18);//get rid of unimportant
    	vector<int> acceptingState;
		int statePush;
		string conc;
		for(int i = 0; i < buffer.length(); i++)
		{
			conc = "";
			if(isdigit(buffer[i+1]) && isdigit(buffer[i]) && 
			   isdigit(buffer[i+2]) && isdigit(buffer[i+3]))
			{
				conc += buffer[i];
				conc += buffer[i+1];
				conc += buffer[i+2];
				conc += buffer[i+3];
				statePush = stoi(conc);
			    acceptingState.push_back(statePush);
				i = i + 4;
			}
			if(isdigit(buffer[i+1]) && isdigit(buffer[i]) && 
			   isdigit(buffer[i+2]))
			{
				conc += buffer[i];
				conc += buffer[i+1];
				conc += buffer[i+2];
				statePush = stoi(conc);
			    acceptingState.push_back(statePush);
				i = i + 3;
			}
			if(isdigit(buffer[i+1]) && isdigit(buffer[i]))
			{
				conc += buffer[i];
				conc += buffer[i+1];
				statePush = stoi(conc);
			    acceptingState.push_back(statePush);
				i = i + 2;
			}
			if(isdigit(buffer[i]))
			{
				conc = buffer[i];
				statePush = stoi(conc);
				acceptingState.push_back(statePush);
			    i++;
			}
		}
		
////////////////////////////////////////////////////////////////////////////////
		//Get the alphabet as an Array
		getline(myReadFile,buffer);
		buffer.erase(0,10);//get rid of unimportant
		int alphaLength = buffer.length();//number of choices in alphabet
		vector< vector<int> > dfaTable;
		dfaTable.resize(numInt, vector<int>(alphaLength, 0));
		string sendAlphabet = buffer;
		vector<char> alphabet[alphaLength]; //alphabet as char array


////////////////////////////////////////////////////////////////////////////////
		//populate the DFA table
		string putTogether;
		int stringCount;
		int arrayInCount;
		for(int i = 0; i < numInt; i++)
		{
			getline(myReadFile,buffer);
			arrayInCount = 0;
			for(int j = 0; j < buffer.length(); j++)
			{
				putTogether = buffer[j];
				if(isdigit(buffer[j]) && isdigit(buffer[j+1]) &&
				   isdigit(buffer[j+2]) && isdigit(buffer[j+3]))
				{
					putTogether = putTogether + buffer[j+1] + 
							      buffer[j+2] + buffer[j+3];
					j = j + 4;
				}
				else if(isdigit(buffer[j]) && isdigit(buffer[j+1]) &&
				        isdigit(buffer[j+2]))
				{
					putTogether = putTogether + buffer[j+1] + 
							      buffer[j+2];
					j = j + 3;
				}
				else if(isdigit(buffer[j]) && isdigit(buffer[j+1]))
				{
					putTogether = putTogether + buffer[j+1];
					j = j + 2;
				}
				else
				{
					j++;
				}
				stringCount = 0;
				for(int k = 0; k < putTogether.length(); k++)
				{
					
					if(isdigit(putTogether[k]))
					{
						stringCount++;
					}
					if(stringCount == putTogether.length())
					{
						int insertToArray = stoi(putTogether);
						dfaTable[i][arrayInCount] = insertToArray;
						arrayInCount++;
					}
				}
			}
		}
	myReadFile.close();

	filename2 = argv[2];
	myReadFile.open(filename2.c_str());
	string testString;
	while(getline(myReadFile,testString))
	{
		testDFA(testString, dfaTable, acceptingState, sendAlphabet);
	}
	myReadFile.close();
	}
	return 0;
}
