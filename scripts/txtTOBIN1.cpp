#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

//int *fields;
typedef struct {
   int *fields;
} RECORD_TYPE;

RECORD_TYPE r;

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


void readFile(ifstream *infile, int count){
   
   string line, word;

   while(getline(*infile,line)){
	if(line.size() == 0)
		continue;
	vector<string> words = split(line, " ");
        if(words.size() == 1)continue;
	
	//cout<<"words size "<<words.size()<<endl;
	//int *fields = new int[words.size()];
	vector<string> words1 = split(words[0], ":");
	string node = "-" + words1[0];
	int nodeInt = atoi(node.c_str());
	if(nodeInt == 0)cout<<" 0 is a node"<<endl;
	r.fields[count] = nodeInt;
	count++;	
	for(int j=1; j< words.size();j++){
		//cout<<words[j]<<" ";
		r.fields[count] = atoi(words[j].c_str());
		count++;
	}
		
   }
}

int main(int argc, char **argv){

   if(argc < 3 ){
	cout<<" usage: ./txtTOBIN euFile.txt nodes edges"<<endl;
	exit(1);
   }

   ifstream *infile = new ifstream(argv[1]);
   if(!infile){
	cout<<" file "<<argv[1]<<" does not exists"<<endl;
	exit(1);
   }

   string fileout = argv[1];
   fileout = fileout + ".bin";
   int numNodes = atoi(argv[2]);
   int numEdges = atoi(argv[3]);
   //cout<<" numNodes "<<numNodes<<" numEdges "<<numEdges<<endl;
   int size = numNodes + numEdges + 2;
   FILE* g; // create a new file pointer
   if((g=fopen(fileout.c_str(),"wb"))==NULL) { //
       printf("could not open file"); // print
       exit(1);
   }


   r.fields = new int[size];
   r.fields[0] = numNodes;
   r.fields[1] = numEdges;
   
   int count = 2;
   readFile(infile, count);
   infile->close();
   delete infile;

   
/*
   for(int k=0; k<size;k++){
	cout<<r.fields[k]<<" ";
   }
   cout<<endl;
*/
   
   for(int k=0; k<size;k++){
   	if(fwrite(&r.fields[k],sizeof(uint),1,g) != 1){
         	printf(" error al escribir en archivo bin \n");
         	exit(1);
   	}
   }

   delete [] r.fields;
   
   return 0;

}
