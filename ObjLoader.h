#ifndef OBJ_LOADER__
#define OBJ_LOADER__

#include "Vector.h"
using namespace mathtool;

#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Face {
  //int id1, id2, id3; //indices into v
  //int t_id1, t_id2, t_id3; //indices into vt
  //int n_id1, n_id2, n_id3; //indices into vn
  void Print() {
    cout << "face ids: ";
    for(int i=0; i<(int)ids.size(); i++) 
      cout << ids[i] << " ";
    cout << endl;
  }
  vector<int> ids;
  vector<int> texIds;
  vector<int> normalIds;

};

class ObjLoader {
public:
  ObjLoader() { }
  ObjLoader(string _fname) { filename = _fname; }

  void Load(); 
  void Print();

//protected:
  string filename;
  vector<Vector3d> verts;
  vector< pair<double, double> > vts;
  vector<Vector3d> vns;
  vector<Face> faces;


};


#endif
