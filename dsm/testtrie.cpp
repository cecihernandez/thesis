#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

#include "Trie.h"

using namespace std;

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

void printVector(vector<unsigned int> v){
	for(unsigned int i=0; i<v.size(); i++)
		cout<<v[i]<<" ";
	cout<<endl;
}

void readFile(ifstream *infile, map<unsigned int, vector<unsigned int> > &adjlist){

   string line, word;

   while(getline(*infile,line)){
        //cout<<"line "<<line<<endl;
        if(line.size() == 0)
                continue;
        vector<int> words = splitToInt(line, " ");
	vector<unsigned int> outlink;
	unsigned int currentNode = (unsigned int)words[0];
	for(unsigned j=1; j<words.size(); j++){
		outlink.push_back((unsigned int)words[j]);
	}
	sort(outlink.begin(), outlink.end());
	adjlist[currentNode] = outlink;
   }
}


int main(int argc, char *argv[]){

  if(argc < 2){
	cout<<"usage: ./testtrie file \n";
	exit(1);
  }

  map<unsigned int, vector<unsigned int> > adjlist;
  map<unsigned int, vector<unsigned int> >::iterator mit;

  ifstream *infile = new ifstream(argv[1]);
  if(!infile){
       cout<<" file "<<argv[1]<<" does not exists"<<endl;
       exit(1);
  }


  readFile(infile, adjlist);

  Trie t;
  for(mit=adjlist.begin(); mit != adjlist.end(); mit++){
      vector<unsigned int> outlink = mit->second;
      unsigned int v = mit->first;
      t.insert(v,outlink);
  }
  //t.printTrie();

  vector<pair< vector<unsigned int> , vector<unsigned int> > > potentialVN;
  vector<pair< vector<unsigned int> , vector<unsigned int> > >::iterator it;
  t.generateVirtualNodeList(potentialVN);

  for(unsigned int i=0; i<potentialVN.size(); i++){
	vector<unsigned int> vs = (potentialVN[i]).first;
	vector<unsigned int> labelpath = (potentialVN[i]).second;
	cout<<" vertexSet "<<endl;
        printVector(vs);
	cout<<" labelpath "<<endl;
  	printVector(labelpath);
  } 
  t.makeEmpty();

}
