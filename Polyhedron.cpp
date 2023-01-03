#include <GL/glut.h>  // (or others, depending on the system in use)

#include "Polyhedron.h"


Polyhedron::Polyhedron(string _fname, Vector3d _c, double _rotY, Vector3d _clr) : ObjLoader(_fname) {
  //cout << "Polyhedron constructor. " << endl;
  center = _c;
  rotY = _rotY;
  color = _clr;
}

Polyhedron::Polyhedron(const Polyhedron& other) {
  //cout << "Polyhedron copy constructor. " << endl;
  center = other.center;
  rotY = other.rotY;
  color = other.color;
  filename = other.filename;
  //////////////////////////////////////////////////////////
  //other data from obj loader

  verts = other.verts;
  vts = other.vts;
  vns = other.vns;
  faces = other.faces;
}

void Polyhedron::Recenter() {
  //TODO 
	Vector3d com;
	for (int i = 0; i < verts.size(); i++) {
		Vector3d& v = verts[i];
		com += v;
	}
	com /= 1.0*verts.size();

	for (int i = 0; i < verts.size(); i++) {
		Vector3d& v = verts[i];
		v -= com;
	}

}

void Polyhedron::RecenterXZ() {
  //TODO 
	Vector3d com;
	for (int i = 0; i < verts.size(); i++) {
		Vector3d& v = verts[i];
		com += v;
	}
	com /= 1.0*verts.size();
	com.SetY(0);

	for (int i = 0; i < verts.size(); i++) {
		Vector3d& v = verts[i];
		v -= com;
	}
}

void Polyhedron::Draw() {
  //TODO

//	for (vector<Face>::iterator f = faces.begin(); f != faces.end(); f++) {
//		(*f).Print();
//	}
  //cout << "Polyhedron::Draw color = " << color << endl;

	glPushMatrix();

	glTranslated(center.GetX(), center.GetY(), center.GetZ());
	glRotated(rotY, 0, 1, 0);
	glColor3dv(color);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < (int)faces.size(); i++) {
			Face& f = faces[i];

			Vector3d& v1 = verts[f.ids[0] - 1];
			Vector3d& v2 = verts[f.ids[1] - 1];
			Vector3d& v3 = verts[f.ids[2] - 1];

			Vector3d nf = (v2 - v1).normalize() % (v3 - v2).normalize();

			glNormal3dv(nf);

			glVertex3dv(v1);
			glVertex3dv(v2);
			glVertex3dv(v3);

		}
		glEnd();
	
		glPopMatrix();
}
