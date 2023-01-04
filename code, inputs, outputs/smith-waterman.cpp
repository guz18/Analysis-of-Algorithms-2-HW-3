// GÖKSU GÜZ - 150180715

#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <map>
#include <algorithm> //only for sort operation
#include <vector>
#include<list>
#include <limits.h>

using namespace std;

class Graph{
public:
    int **graph;

    vector<string> wordsFromTheFile;
    int sizeOfTheInput = 0;

    vector<string> sameLetters;
    int countOfTheMaxLetter = 0;
    void searchAlgorithm(string, string, int, int);
    
    void putTheWord(string, int, int);

};

void Graph::putTheWord(string word,int sizeFirst, int sizeSecond){
    sameLetters.clear();
    for(int i = 1; i < sizeFirst + 1; i++){
        for(int j = 1; j < sizeSecond + 1 ; j++){
            string ptr;
            if(graph[i][j] == countOfTheMaxLetter){
                int x = i;
                int y = j;
                while(graph[x][y] != 0){
                    x--;
                    y--;
                }
                x += 1;
                y += 1;
                int t = 0;
                for(; t + x <= i ; t++)
                    ptr += word[x + t - 1];
                int tx = sameLetters.size();
                int m = 0;
                for(int a = 0; a < tx; a++){
                    if(ptr.compare(sameLetters[a]) == 0){
                        m = 1;
                    }
                }
                if(m == 0){
                    sameLetters.push_back(ptr);
                }
            }
        }
    }
}

void Graph::searchAlgorithm(string first, string second, int match1, int match2){
    int match = match1;
    int mismatch = match2;
    countOfTheMaxLetter = 0;
    sameLetters.clear();
    int sizeFirst = first.length();
    int sizeSecond = second.length();
    int gap_penalty = -100;

    graph = new int*[sizeFirst + 1];
    for(int i = 0; i < sizeFirst + 1; i++){
        graph[i] = new int[sizeSecond + 1];
    }

    //to make first row and column zero 
    for(int i = 0; i < sizeFirst + 1; i++){
        graph[i][0] = 0;
    }
    for(int i = 0; i < sizeSecond + 1; i++){
        graph[0][i] = 0;
    }

    for(int i = 1; i < sizeFirst + 1; i++){
        for(int j = 1; j < sizeSecond + 1 ; j++){
            int temp = 0;
            if(first[i-1] == second[j-1])
                temp =  graph[i-1][j-1] + match;
            else
                temp =  graph[i-1][j-1] + mismatch;
            int z =  max(graph[i-1][j]+gap_penalty, graph[i][j-1]+gap_penalty);
            z = max(z , temp);
            z = max(z, 0);
            graph[i][j] =  z;
            if(z > countOfTheMaxLetter){
                countOfTheMaxLetter = z;   
            } 
        }
    }    
    putTheWord( first, sizeFirst,  sizeSecond);
    std::sort(sameLetters.begin(),sameLetters.end());
}

int main(int argc, char **argv){

    int temp1 = 1;
    int temp2 = -2;
    string in = "strings.txt";
    string out = "output.txt";

    if(argc>1){
        in = argv[1];
        out = argv[2];
    }
    if(argc>3)
    {
        temp1 = stoi(argv[3]);
        temp2 = stoi(argv[4]);
    }
    ifstream myFile(in);
    //Read the file
	if (!myFile.is_open()) {
		cerr << "FILE COULD NOT BE FOUND" << endl; 
		exit(1);
	}

    Graph g;
    string line;

    //This the input storing part
    for (int i = 0 ; !myFile.eof() ; i++) { 
        getline( myFile, line, '\n' );
        g.wordsFromTheFile.push_back(line);
        g.sizeOfTheInput = i + 1;
    }
    myFile.close();

    std::sort(g.wordsFromTheFile.begin(),g.wordsFromTheFile.end());

    ofstream myfile;
    myfile.open(out, std::fstream::in|std::ios::out | std::ios::trunc);

    for(int i = 0; i < g.sizeOfTheInput; i++)
    {
        for (int j = i + 1; j < g.sizeOfTheInput; j++){
            g.searchAlgorithm(g.wordsFromTheFile[i], g.wordsFromTheFile[j], temp1, temp2);
            int tx = g.sameLetters.size();
            myfile << g.wordsFromTheFile[i] << " - " <<g.wordsFromTheFile[j] << endl;
            myfile << "Score: " << g.countOfTheMaxLetter << " Sequence(s):";
            if (g.countOfTheMaxLetter == 0);
            else{
                for(int i = 0; i < tx; i++){
                    myfile <<" \"" <<g.sameLetters[i] << "\"" ;
                }
            }
            myfile << endl;
        }
    }
    myfile.close();
 
    return 0;
}