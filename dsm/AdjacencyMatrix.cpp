#include "AdjacencyMatrix.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cassert>
#include <algorithm>

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

string AdjacencyMatrix::int2String(int i){
   stringstream ss;
   string str;
   ss<<i;
   ss>>str;
   return str;
}

string AdjacencyMatrix::double2String(double i){
   stringstream ss;
   string str;
   ss<<i;
   ss>>str;
   return str;
}

//load bin file in Francisco format, bin file created with 
// txtTOBIN which creates bin file from txt file and 
// it does not create the entries for nodes with outlinks cero

void AdjacencyMatrix::loadBinFileFranFormat(const char * filename){
  FILE *fp = fopen64(filename,"r");
  if(fp==NULL)
        cout<<" error opening file "<<filename<<"\n";
  assert(fp!=NULL);

  uint rd = 0;

  uint nodes; uint edges;
  rd += fread(&nodes,sizeof(uint),1,fp);
  rd += fread(&edges,sizeof(uint),1,fp);

  unsigned int currentNode = 0;
  vector<unsigned int> aux;
  vector<unsigned int>::iterator vit;

  cout<<" nodes "<<nodes<<" edges "<<edges<<"\n";
  cout.flush();
  totalOriginalEdges = edges;
  for(uint i=0;i<nodes+edges;i++) {
    int k;
    rd += fread(&k,sizeof(unsigned int),1,fp);
    if(k<0) {
      if(aux.size() != 0){
	    // adding same node to the outlink to catch cliques
	    vit = find(aux.begin(), aux.end(), currentNode);
	    if(vit == aux.end())
		aux.push_back(currentNode);
	    sort(aux.begin(), aux.end());
	    //
            matrix.push_back(make_pair(aux, currentNode));
      }
      if(totNodes < -k)
	totNodes = -k;
      aux.clear();
      currentNode = -k;

    }
    else {
      aux.push_back(k);
      if(totNodes < k)
	totNodes = k;
    }
  }
  if(aux.size() != 0){
     // adding same node to the outlink to catch cliques
     vit = find(aux.begin(), aux.end(), currentNode);
     if(vit == aux.end())
	aux.push_back(currentNode);
     sort(aux.begin(), aux.end());
     //
     matrix.push_back(make_pair(aux, currentNode));
  }
  fclose(fp);
  totNodes++;
  cout<<"vns comienzan en "<<totNodes<<"\n";
  cout.flush();

}


// dump a single row 


void AdjacencyMatrix::dumpRow(int row) const{

  cout << "`" << matrix[row].second << "'\t";
  vector<unsigned int> outlink = matrix[row].first;
  vector<unsigned int>::iterator it;
  for(it = outlink.begin(); it != outlink.end(); it++) 
	cout<<*it<<" ";
  cout<<"\n";
}


// dump all the rows 

void AdjacencyMatrix::dumpFile() const{

  MatrixMap::const_iterator end = matrix.end();

  //unsigned row = 0;
  for (MatrixMap::const_iterator it = matrix.begin();
       it != end;
       it ++){

    //cout <<it->second<<":"<<it->first  <<"\n";
	cout<<it->second<<":";
  	vector<unsigned int> outlink = it->first;
  	vector<unsigned int>::iterator vit;
  	for(vit = outlink.begin(); vit != outlink.end(); vit++) 
		cout<<*vit<<" ";
  	cout<<"\n";
  
  }
}

// dump all the rows to a file

void AdjacencyMatrix::dumpFile(string filename, unsigned currentIter, unsigned maxIter) const{

  ofstream *out = NULL;
  //FILE *fp = NULL;
  if(currentIter == maxIter)
	//fp = fopen64(filename.c_str(),"w");
	out = new ofstream(filename.c_str());

  filename = filename + ".res";
  ofstream res(filename.c_str());
  string strout = "entering dumpFile";
  res.write(strout.c_str(),strout.size());
  res.put('\n');
  res.flush();
  int edges = 0;
  for (MatrixMap::const_iterator it = matrix.begin();
       it != matrix.end();
       it ++){
			//int vertex = - (it->second); 
			//my_fwrite(&vertex, sizeof(int), 1, fp);
		edges += (it->first).size();
  		if(currentIter == maxIter){
			// must eliminate vertex where the outlink is only the same
			// vertex, because was added to identify cliques as bicliques
			unsigned int vertex = it->second;
  			vector<unsigned int> outlink = it->first;
  			vector<unsigned int>::iterator vit;
			vector<unsigned int> outlink2;
			for(unsigned int k = 0; k<outlink.size(); k++){
				if(outlink[k] != vertex)
					outlink2.push_back(outlink[k]);
			}
			if(outlink2.size() == 0) continue;

			string str = int2String(it->second);

			out->write(str.c_str(),str.size());
			out->put(':');
			out->flush();
  			//vector<unsigned int> outlink = it->first;
  			//vector<unsigned int>::iterator vit;
			string s;
  			for(vit = outlink2.begin(); vit != outlink2.end(); vit++) {
				s = s + " " + int2String(*vit);
				//int arc = *vit;
				//my_fwrite(&arc, sizeof(int), 1, fp);
			}
			out->write(s.c_str(),s.size());
			out->flush();
			out->put('\n');
			out->flush();
		}
  }
  if(currentIter == maxIter){
  	//fclose(fp);
	out->close();
	delete out;
  }
  double compressionRate = 1.*totalOriginalEdges / edges;
  string strComp = double2String(compressionRate);
  res.write(strComp.c_str(), strComp.size());
  res.flush();
  cout<<"i="<<currentIter<<" compressionRate="<<compressionRate<<" edges="<<edges<<endl;
  cout.flush();
}


