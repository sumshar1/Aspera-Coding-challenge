/* Programming Problem == Find longest words made of other words
   Language used C++ */

/* header files */
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<map>
#include<string>
#include<string.h>
#include<unistd.h>


/*map deceleration for storing the words*/

std::map<std::string, std::string> WordMap;
std::map<std::string, std::string>::iterator mapIt1;
std::map<std::string, std::string>::iterator mapIt2;

/*global string so that it can be remembered accross all WordBreaker Function calls*/

std::string stringGlobal;

/* total words that can be formed out of small words */

long int totalwords(0);

/*--->>>function decelerations */

/* 1) To read the given input file by the name "wordsforproblem.txt" and store all its words in a sorted  map.
     The time complexity to do so would be O(N), as the file we read are already sorted.
*/
bool ReadInputfile(std::string filename);

/* 2) matching the word to see if it can be formed out of small words, it is a recursive function. It starts forming prefixes and starts checking them from length 1 in the map, if the prefix matches, then the same happens for remaining word. if the match is not found then we backtrack and try for different prefixes.
*/

bool WordBreaker(std::string Sstring);


/* ---->>>function definitions */

/* defining ReadInputFile function */

bool ReadInputfile(std::string filename)
{
	//opening the file in  input mode
	std::ifstream input_file(filename.c_str(), std::ios::in);

	//try catch exception block to check the existence of file or else exit.
		try
		{
		if(!input_file)
			  throw 1;		
		}

		catch(int exception)
		{
		std::cerr <<"The file you tried to open for input does not exist";
	        return false;
		}
	/* string used to add words from input file to data structure "MAP" */	
	std::string DictionaryWord;


	//if the file exists, we add the contents to a map data structure
	while(input_file)
		{
		input_file>>DictionaryWord;
		WordMap[DictionaryWord]="\0";
		}
	//close the file
	input_file.close();
	return true;
}

/* definition for WordBreaker function */

bool WordBreaker(std::string Sstring)
{
	int size = Sstring.size();

   	/* Base termination case*/
   	if (size == 0)  return true;
   
	/* Try all prefixes of lengths from 1 to maximum size*/
   	for (int lengthx=1; lengthx<=size; lengthx++)
   		{
       		if ( (WordMap.find( Sstring.substr(0, lengthx) ) != WordMap.end() ) && WordBreaker( Sstring.substr(lengthx, size - lengthx) ) && Sstring.substr(0, lengthx) != stringGlobal)
       			{
			return true;
			}
   		}

   	/* none of the possible combinations have worked */
   return false;
}


/* pass file name as argument to the program */
int main(int argc, char *argv[])
{
	if(argc != 2)
		{ 
		std::cerr<<"usage ./solution filename"<<std::endl; exit (0);
		}

	char *fileName=argv[1];
        int returnedStringSize;
	std::string longeststrings[2]={"\0","\0"}; /* strings to store the top 2 longest words */

	bool MapReady = ReadInputfile(fileName);/* reading the file was successful and data structure is ready for use */
	mapIt1=WordMap.begin();

	if( MapReady == true)
		{ /* start reading the words from map and check if they can be formed from other words in the map, other than itself */
		mapIt1 = WordMap.begin();

		while(mapIt1 != WordMap.end())
			{
			stringGlobal = mapIt1->first;
			bool returnValue = WordBreaker(mapIt1->first);
				if(returnValue == false) { ; } //do nothing
				else
					{
					totalwords++;
					std::string output=mapIt1->first;
					returnedStringSize = output.size();
					/*keeping the maximum length 2 longest words */
					if( returnedStringSize > longeststrings[0].size())
 						 {
   						 std::string temp;
						 temp=longeststrings[0];
						 longeststrings[0]=mapIt1->first;
						 longeststrings[1]=temp;
						 }
					else if( returnedStringSize < longeststrings[0].size() && returnedStringSize > longeststrings[1].size())
   						{
						longeststrings[1]="\0";
						longeststrings[1]=mapIt1->first;
						}
					else { ; }
					}
			stringGlobal="\0";
			mapIt1++;
		        }

		std::cout<<"The first longest word  :  "<<longeststrings[0]<<std::endl;
		std::cout<<"The second longest word :  "<<longeststrings[1]<<std::endl;
         	std::cout<<"Total count             :  "<<totalwords;
		return 1;
		}
	else //result==false
	{
		return 0;
	}
}

