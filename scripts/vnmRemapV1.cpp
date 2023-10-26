#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;
map<int,vector<int> > adjlist;
map<int,int> vnodesMap;

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


int readFile(ifstream *infile, int origNodes){
   
   string line, word;
   int totVNodes = 0;

   int vnid = origNodes + 1;
   int i=0;
   while(getline(*infile,line)){
	//cout<<"line "<<line<<endl;
	if(line.size() == 0)
		continue;
	vector<string> words = split(line, " ");
	//cout<<" line "<<line<<endl;
	//cout<<" words size "<<words.size()<<endl;
        if(words.size() == 1 || words[0] == ":")continue;
	int j = 1;
	string currentNode = words[0];
	int nodeid = atoi(currentNode.c_str());
	// constructs maps only for vnodes definitions
	vector<int> outlinks;
	while(j < words.size()){
		int edge = atoi(words[j].c_str());
		outlinks.push_back(edge);
		j++;
	}
	if(nodeid <= origNodes){	
		adjlist[nodeid] = outlinks;
	} else if(nodeid > origNodes){
		i++;
		adjlist[vnid] = outlinks;
		vnodesMap[nodeid] = vnid;
		vnid++;
	}
		
   }
   return origNodes+i;
}

int main(int argc, char **argv){

   int v = 0;

   if(argc < 3 ){
	cout<<" usage: ./vnmRemap euFile.txt numberOrigNodes(maxvertexid in original graph) [0/1] default 0, no debug 0, outputs the text format for BV if not debug and original graph if debug). "<<endl;
	exit(1);
   }

   int origNodes=atoi(argv[2]);
   int debug = 0;
   if(argc == 4){
	debug = atoi(argv[3]);
   }
  
   ifstream *infile = new ifstream(argv[1]);
   if(!infile){
	cout<<" file "<<argv[1]<<" does not exists"<<endl;
	exit(1);
   }
   int numNodes = readFile(infile, origNodes);
   infile->close();
   delete infile;

   cout<<numNodes<<endl;
   map<int, vector<int> >::iterator mit;
   map<int, int >::iterator it;
   vector<int>::iterator vit;
   int curNode=0;

/*
   cout<<" vnodesMap"<<endl;
   for(it = vnodesMap.begin(); it != vnodesMap.end(); it++){
	cout<<it->first<<" "<<it->second<<endl;
   }
*/

  if(debug){
   for(mit = adjlist.begin(); mit != adjlist.end(); mit++){
	cout<<mit->first<<":";
	
	for(vit = (mit->second).begin(); vit!= (mit->second).end(); vit++){
		cout<<" "<<(*vit);
	}
	cout<<endl;
   }
  } else {

   int numEdges = 0;
   for(mit = adjlist.begin(); mit != adjlist.end(); mit++){
	if(mit->first > origNodes) break;
	
	//if(mit->first <= origNodes){	
		if(mit->first - curNode > 1){
			for(int i=curNode+1; i<mit->first; i++)
				cout<<endl;
		}
	//}
	//cout<<"nodo "<<mit->first<<endl;
	for(vit = (mit->second).begin(); vit!= (mit->second).end(); vit++){
		numEdges++;
		if(*vit > origNodes)
			cout<<vnodesMap[*vit]-1<<" ";
		else 
			cout<<(*vit - 1)<<" ";
	}
	curNode = mit->first;
	cout<<endl;
   }
   int numLines=origNodes - curNode;
   for(int j=0; j<numLines; j++)
	cout<<endl;

   map<int, vector<int> >::iterator nit;
   nit = adjlist.find(origNodes + 1);
   for(mit=nit; mit != adjlist.end(); mit++){
	for(vit = (mit->second).begin(); vit!= (mit->second).end(); vit++){
		if(*vit > origNodes)
			cout<<vnodesMap[*vit]-1<<" ";
		else 
			cout<<(*vit - 1)<<" ";
	}
	cout<<endl;
   }
  }
   

   return 0;

}
