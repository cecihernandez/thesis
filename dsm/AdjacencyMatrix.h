#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX 
#include <vector>
#include <map>
#include <string>

#include "Utils.h"

using namespace std;

class AdjacencyMatrix{
  
 public:
  
  static string int2String(int i);
  static string double2String(double i);

  unsigned getNumberROWS(){
	return matrix.size();
  }
  

// first item in pair is the outlink list in string format and the next element in pair is 
// the string that represent the vertex 
//  typedef vector<pair<string,string> > MatrixMap;  
  typedef vector<pair<vector<unsigned int> , unsigned int> > MatrixMap;  

  /* 
   * Read the adjacency list file
   *
   * \param meta index for filename in francisco claude txt format
   *
   */
  void loadBinFileFranFormat(const char * filename);

  // stdout the matrix content by rows
  void dumpFile() const;

  // print matrix to a file content by rows
  void dumpFile(string filename, unsigned currentIter, unsigned maxIter) const;
  void dumpRow(int row) const;

  /*
   * iterators
   */
  typedef MatrixMap::iterator matrix_iterator;
  typedef MatrixMap::const_iterator const_iterator;
  inline matrix_iterator begin() { return matrix.begin();};
  inline matrix_iterator end() { return matrix.end();};
  inline const_iterator cbegin() { return matrix.begin();};
  inline const_iterator cend() { return matrix.end();};
  inline long size() {return matrix.size();}


  AdjacencyMatrix(){totNodes =0; totalOriginalEdges=0;};

  int getNode(){return totNodes;}
  void nextNode(){totNodes++;}
  int totNodes;
  int totalOriginalEdges;

// private:
  MatrixMap matrix;
};


#endif
