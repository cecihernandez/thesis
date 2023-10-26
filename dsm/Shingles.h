#ifndef SHINGLES
#define SHINGLES
#include "AdjacencyMatrix.h"
#include "Trie.h"
#include "Utils.h"
#include <math.h>
#include <stdlib.h>

using namespace std;

class Shingles{

 public:

  typedef unsigned short size_signatures;
  typedef pair<unsigned int, int> sign_node;
  typedef pair<unsigned int, int> sign_nodeString;
  typedef pair<unsigned int, vector<unsigned int> > edge_VertexList;
  typedef vector<sign_node> SignNodeVect;
  typedef vector<sign_nodeString> SignNodeVectString;
  typedef vector<edge_VertexList> SelectedEdges;


  //
  // The constructor, initialize prime_, and  A_, B_, MIN_ vectors
  //
  //

  Shingles(unsigned short numberSignatures,int currentNumRows, unsigned int bs): numberSignatures_(numberSignatures){

    //2^31 - 1 is prime
    prime_ =  static_cast<unsigned int>(pow(2,31)-1);
    srand(time(NULL));
    //srand(1);

    for (unsigned int i = 0; i < numberSignatures; i++){

      A_.push_back( rand() % prime_ + 1);
      B_.push_back( rand() % prime_ + 1);
      MIN_.push_back(prime_ + 1);
    }    
    
    // allocate the space for the comparison of shingles
    signNode.reserve(numberSignatures * currentNumRows);
    bsize = bs;

  };

  void computeShingles(AdjacencyMatrix &,
		       const unsigned short);

  void computeMinHash(AdjacencyMatrix & );

  void computePotentialClusters(PotentialClusters &potClusters, int numberRows);
  void genClusters(int column, PotentialClusters &pot, AdjacencyMatrix &ds);

  void printSignNode();
  void printSignNodeMIN();

  void cleanAll();
  bool transVector(pair<vector<unsigned int>, unsigned int> adj, vector<unsigned int> outlink);

 private:

  void getSortColHash(vector<unsigned int> &matRows, int colNumber,
			 SignNodeVect &col, int ini, int end);
  void makeGroupIes(map<unsigned int, vector<int> > &groups, 
			SignNodeVect &col);
  void makeSortMatrix(vector<unsigned int> &s_rows, 
		vector<unsigned int> &matRows, map<unsigned int, 
		vector<int> > &groups, vector<int> &possibleClusters);
  void miningPhase(vector<unsigned int> &c_rows, AdjacencyMatrix &ds);
  void computeHistogram(vector<unsigned int> &c_rows, const AdjacencyMatrix &ds, 
		  map<unsigned int, vector<unsigned int> > & mapVertexOutlink);
  void reemplazing(vector<unsigned int> &c_rows, 
		VNodeList & mapVNList, AdjacencyMatrix &ds, 
		vector<pair< vector<unsigned int>, 
		vector<unsigned int> > > &potentialVN);
  void printVector(vector<unsigned int> &v);
  void sortClusters(int column, vector<unsigned int> &in_rows, vector<unsigned int> &out_rows, int numberROWS);


  static unsigned uniqueid;
  static VNodeList globalVNList;
  static vector<unsigned int> allvnodes;

  size_signatures numberSignatures_;
  
  unsigned int prime_;

  vector<unsigned int> A_;  // A_, as in a X + b mod prime_
  vector<unsigned int> B_;  // B_, as in a X + b mod prime_
  vector<unsigned int> MIN_;// current MIN_HASH

  SignNodeVect signNode;      // contains the pairs <signature, int>
  unsigned int bsize;


  // used for comparing signNode
  struct orderSignNode{

    bool operator()(const sign_node& rpStart, const sign_node& rpEnd ){
//	return rpStart.second < rpEnd.second;
      if (rpStart.second == rpEnd.second)         // in case of tie on index 
	return rpStart.first > rpEnd.first; // order by hash 
      else        
	return rpStart.second < rpEnd.second;
    }
  };
 
  struct compareSignNode{

    bool operator()(const sign_node& rpStart, const sign_node& rpEnd ){
    
      if (rpStart.first == rpEnd.first)         // in case of tie on shingle
	return rpStart.second < rpEnd.second; // order by Rows
      else        
	return rpStart.first > rpEnd.first;
    }
  };

  // used to look for the edge in the histogram vector (counts) to 
  // increment its counter

  struct myfunction{

    bool operator()(const sign_nodeString& rpStart, const sign_nodeString& rpEnd ){
      return (rpStart.first == rpEnd.first);         
    }
  };

  // used to sort the edge histogram from higher to lower count

  struct myCompare{

    bool operator()(const sign_nodeString& rpStart, const sign_nodeString& rpEnd ){
      return (rpStart.second > rpEnd.second);         
    }
  };

  struct edgeCmp{

    bool operator()(const edge_VertexList& rpStart, const edge_VertexList& rpEnd ){
      if ((rpStart.second).size() == (rpEnd.second).size())         // in case of tie on shingle
	//return atoi(rpStart.first.c_str()) < atoi(rpEnd.first.c_str()); // order by edge number
	return rpStart.first < rpEnd.first; // order by edge number
      else 
        return ((rpStart.second).size() > (rpEnd.second).size() );
    }
  };


  struct CompareSaving{
     bool operator()(const pair<vector<unsigned int>, vector<unsigned int> > & rpStart, const pair<vector<unsigned int>, vector<unsigned int> > & rpEnd ){
	
     	int saving1 = ((rpStart.first).size() - 1) * ((rpStart.second).size() - 1);
     	int saving2 = ((rpEnd.first).size() - 1) * ((rpEnd.second).size() - 1);
     	if (saving1 == saving2) {
           	return ((rpStart.second).size() > (rpEnd.second).size());
     	} else {
         	return (((rpStart.first).size() - 1) * ((rpStart.second).size() - 1) > ((rpEnd.first).size() - 1) * ((rpEnd.second).size() - 1));
     	}


     }
 };


};

#endif
