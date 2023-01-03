#ifndef _POLYHEDRON_
#define _POLYHEDRON_

#include "ObjLoader.h"

class Polyhedron : public ObjLoader {
public:
  Polyhedron(string _fname, Vector3d _c, 
  	double _rotY, Vector3d _clr);
  Polyhedron(const Polyhedron& other);

  void Draw();
  void Recenter();
  void RecenterXZ();

  Vector3d center;
  double rotY;
  Vector3d color;
};

#endif
