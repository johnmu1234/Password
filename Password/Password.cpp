// PasswordGen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool not_space( char c )
{
	return !isspace(c & 255);
}
bool space( char c )
{
	return 0 != isspace(c & 255);
}

bool notRequired( char c )
{
	string notRequiredChars = string( ".,![]{}()\';+\"\\0123456789`:" );
	string::const_iterator it;
	it = find( notRequiredChars.begin(), notRequiredChars.end(), c );
	if( it != notRequiredChars.end() )
		return true;
	return false;
}

int myRand( int minNumber, int maxNumber )
{
	int random;
	do
	{
		random = rand();

	} while( (random < minNumber) || (random > maxNumber) );

	return random;
}

// Main function, no parameters used - yet!
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream	infile;
	map<string, int> words;

	infile.open("mykeys.txt", ifstream::in );
	if( !infile.is_open() )
		return -1;

	string line;
	while( getline( infile, line ) )
	{
		string::iterator it = line.begin();
		while( it != line.end() )
		{
			it = find_if(it, line.end(), not_space );

			string::iterator it1 = find_if(it, line.end(), space );

			string word = string(it, it1);

			string::iterator it2 = word.begin();
			string::iterator it3 = remove_if( it2, word.end(), notRequired );
			string word2 = string(it2, it3);

			string::size_type wordLen = word2.length();
			if( (wordLen > 4) && (wordLen < 7) )
			{
			   word2[0] = toupper( word2[0] );
				words[word2]++;
			}

			it = it1;
		}
	}
	infile.close();

	unsigned int randSeed = (unsigned int)time(NULL);
	srand( randSeed );

	int rand1 = myRand( 0, words.size() );
	int rand2 = myRand( 0, words.size() );
	int rand3 = myRand( 100, 1000 );

	map<string, int>::iterator wit1 = words.begin();
	for( int xx = 0; xx < rand1; xx++ )
		wit1++;

	map<string, int>::iterator wit2 = words.begin();
	for( int xx = 0; xx < rand2; xx++ )
		wit2++;

	cout << wit1->first << wit2->first << rand3;
	return 0;
}

