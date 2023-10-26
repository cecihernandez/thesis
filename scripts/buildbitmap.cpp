#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>

using namespace std;

void readFile(ifstream *infile, int firstvn, vector<unsigned int> &bitmap){

   string line, word;

   int i=0;
   while(getline(*infile,line)){
        if(line.size() == 0)
                continue;
        int currentNode = atoi(line.c_str());
        if(i >= firstvn)
                bitmap[currentNode] = 1;
        i++;
   }
   return;
}

int main(int argc, char **argv){


   if(argc < 4 ){
        cout<<" usage: ./buildbitmap eu.map firstvn maplenth"<<endl;
        exit(1);
   }

   ifstream *infile = new ifstream(argv[1]);
   int firstvn = atoi(argv[2]);
   int maplength = atoi(argv[3]);
   vector<unsigned int> bitmap;
   for(int i=0; i<maplength; i++)
        bitmap.push_back(0);
   if(!infile){
        cout<<" file "<<argv[1]<<" does not exists"<<endl;
        exit(1);
   }
   readFile(infile,firstvn, bitmap);
   infile->close();
   delete infile;


   for(int i=0; i<maplength; i++)
        cout<<bitmap[i]<<endl;


   return 0;

}

