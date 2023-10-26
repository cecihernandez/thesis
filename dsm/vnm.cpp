#include <iostream>

#include <boost/program_options.hpp>

#include "AdjacencyMatrix.h"
#include "Shingles.h"
#include "Utils.h"

#include <ctime>                           // for timing

using namespace std;

static unsigned currentPass;

int main(int argc, char *argv[]){

  unsigned int shingle_size;
  unsigned int num_hashes = 8; 
  int format = 0;
  string outfile;

  if(argc < 8){
	cout<<"usage: ./vnm file format[1: binary (like Claude but without empty adj lists)] numShingles iter outputDir_and_file num_hashes bsize\n";
	exit(1);
  }
  format = atoi(argv[2]);
  shingle_size = atoi(argv[3]);
  unsigned iters = atoi(argv[4]);
  outfile = argv[5]; 
  num_hashes = atoi(argv[6]);
  unsigned int bsize = (unsigned int)atoi(argv[7]);
  
  //
  // create and load the graph space
  //
  cout<<" filename input "<<argv[1]<<" format "<<format<<" shingle_size "<<shingle_size<<" outfile "<<outfile<<" num_hashes "<<num_hashes<<" bsize "<<bsize<<endl;

  AdjacencyMatrix ds;
  if(format == 0){
	cout<<"txt format not supported\n";
	exit(1);
  } else {
	ds.loadBinFileFranFormat(argv[1]);
	//ds.dumpFile();
	//exit(1);
  }

  clock_t start, finish;
  double time;
  start = clock();

  string filename;
  string itstr;


  for(unsigned i = 0 ; i < iters; i++){
	//cout<<" ITER "<<i<<"\n";
  	int numberRows = ds.getNumberROWS();
  	//Shingles sh(num_hashes, numberRows);
  	Shingles *sh = new Shingles(num_hashes, numberRows, bsize);
	currentPass = i;
  	sh->computeShingles(ds, shingle_size);

  	PotentialClusters pClusters;
  	sh->computePotentialClusters(pClusters, numberRows);
  	sh->genClusters(2,pClusters,ds);
  	sh->cleanAll();
	delete sh;

  	//cout<<"Adjacency Matrix i "<<i<<"\n";
	itstr = AdjacencyMatrix::int2String((int)i);
	filename = outfile + "-it-" + itstr;
  	ds.dumpFile(filename, i, iters-1);
  }


  finish = clock();
  time = double(finish - start) / CLOCKS_PER_SEC;
  cout << "\t elapsed time " << time << endl;


}
