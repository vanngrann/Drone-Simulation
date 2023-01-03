#include "ObjLoader.h"
#include "Polyhedron.h"

#include <fstream>

void ObjLoader::Load() {
  if( filename == "" ) {
    cout << "Cannot load. empty file name!" << endl;
    exit(-1);
  }
  cout << "ObjLoader::Loading file: " << filename << endl;
  ifstream infile;
  infile.open(filename.c_str());
  string stmp;
  while( infile >> stmp ) {
    if( stmp == "v" ) {
      //Vector3d v;
      //infile >> v;
		double x, y, z;
		infile >> x >> y >> z;
		Vector3d v(x, y, z);
      verts.push_back( v );
    }
    else if( stmp == "vn" ) {
      //Vector3d v;
      //infile >> v;
	  double x, y, z;
	  infile >> x >> y >> z;
	  Vector3d v(x, y, z);
      vns.push_back( v );
    }
    else if( stmp == "vt" ) {
      pair<double,double> tmpPair;
      infile >> tmpPair.first >> tmpPair.second;
      vts.push_back( tmpPair );
    }
    else if( stmp == "f" ) {
      //assume triangle
      Face f;
      for(int i=0; i<3; i++) {
	int vid = -1;
	int nid = -1;
	int tid = -1;
	infile>>vid;//first read vertex id
	bool done = false;
	char c = infile.peek();
	if( c == '/' ) {
	  infile.get(c); //should read '/' 
	  c = infile.peek();
	  if( c == '/' ) { //no texture coordinate
	    infile.get(c); //grab '/'
	    infile >> nid;
	    done = true;
	  }
	  else {
	    infile >> tid;
	    c = infile.peek();
	    if( c == '/' ) {
	      infile.get(c);
	      infile >> nid;
	      done = true;
	    }
	    else done = true;
	  }
	}
	else if( c == ' ' ){
	  done = true;
	}
	if(done) {
           f.ids.push_back( vid );
           f.texIds.push_back( tid );
	   f.normalIds.push_back( nid );
	}
      }//endfor i
      faces.push_back( f );
    }
    else {
      //skip this line if it doesn't start with v, vn, vt, f
      getline(infile, stmp);
    }
  }
  infile.close();
  cout << "-done! ObjLoader::Loading file: " << filename << endl;
}
/*
loadFile(string filename)
ifstream infile;
infile.open(filename.c_string())
int numObjs;
infile >> numObjs;

for(int i=0; i < numObjs; i++){
string f_name;
vector3d trans;
string recenterType;
double rot, scal;

infile >> f_name >> trans >> recenterType >> rot >> scale;

Polyhedron p_i(f_name, trans, rot, color);
p_i.Load();
if(recenterType == "Recenter"){
		p_i.Recenter();
	}
	else
	p_i.RecenterXZ();
	polys.push_back();
}


*/

void ObjLoader::Print() {
  cout << "ObjLoader::Print()" << endl;
  cout << "#verts " << verts.size() << endl;
  for(int i=0; i<verts.size(); i++) {
    cout << "v " << verts[i] << endl;
  }
  cout << endl;
  cout << "#normals " << vns.size() << endl;
  for(int i=0; i<vns.size(); i++) {
    cout << "vn " << vns[i] << endl;
  }
  cout << "#texture coordinates " << vts.size() << endl;
  for(int i=0; i<vts.size(); i++) {
    cout << "vt " << vts[i].first << " " << vts[i].second << endl;
  }
  cout << "#faces " << faces.size() << endl;
  for(int i=0; i<faces.size(); i++) {
    Face& f = faces[i];
    cout << "f ";
    for(int i=0; i<f.ids.size(); i++) {
      cout << f.ids[i] << "/" << f.texIds[i] << "/" << f.normalIds[i] << " ";
    }
    cout << endl;
  }

}

