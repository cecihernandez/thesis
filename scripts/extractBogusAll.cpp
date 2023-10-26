#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <string.h>

#define GMR_HDR 4

using namespace std;


int numBicliques = 0;
int totalBicliqueElems = 0;
int numElements = 0;
int maxelem = 0;

vector<string> split(string line, string delims){
   string::size_type bi, ei;
   vector<string> words;
   bi = line.find_first_not_of(delims);     
   while(bi != string::npos) {
  	ei = line.find_first_of(delims, bi);
    	if(ei == string::npos)
      		ei = line.length();
    		words.push_back(line.substr(bi, ei-bi));
    		bi = line.find_first_not_of(delims, ei);
  	}                 
  return words;
}

vector<int> splitToInt(string line, string delims){
   string::size_type bi, ei;
   vector<int> words;
   bi = line.find_first_not_of(delims);     
   while(bi != string::npos) {
  	ei = line.find_first_of(delims, bi);
    	if(ei == string::npos)
      		ei = line.length();
		string aux = line.substr(bi, ei-bi);
    		words.push_back(atoi(aux.c_str()));
    		bi = line.find_first_not_of(delims, ei);
  	}                 
  return words;
}

string int2String(int i){
   std::stringstream ss;
   std::string str;
   ss<<i;
   ss>>str;
   return str;
}

void readFile(ifstream *infile){
   
   string line, word;
   int totNodes,totEdges;
   int currentNode, value;
   map<int, bool>::iterator mit;

   while(getline(*infile,line)){
	//cout<<"line "<<line<<endl;
	if(line.size() == 0)
		continue;
	vector<string> words = split(line, ":");
        if(words.size() == 1)continue;
	int currentNode = atoi(words[0].c_str());
	vector<int> outlinks = splitToInt(words[1]," ");

	vector<int> outlinks2;
	for(unsigned int i=0; i<outlinks.size(); i++){
		if(currentNode != outlinks[i])
			outlinks2.push_back(outlinks[i]);
	
	}

	if(outlinks2.size() == 0) continue;
	
	cout<<currentNode<<":";
	for(unsigned int i=0; i<outlinks2.size(); i++)
		cout<<" "<<outlinks2[i];
	cout<<endl;

   }
   return;
}

int main(int argc, char **argv){

   if(argc != 2 ){
	cout<<" usage: ./extractBogusAll remainingFile (outputs remaining graph, without self Ref nodes)"<<endl;
	exit(1);
   }

   string filename = argv[1];
   ifstream *infile = new ifstream(filename.c_str());
   if(!infile){
	cout<<" file "<<argv[1]<<" does not exists"<<endl;
	exit(1);
   }
   readFile(infile);
   infile->close();
   delete infile;
   
   return 0;

}
