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
	glScalef(10.0, 10.0, 10.0);
	//glColor3dv(color);
	glColor3d(color.GetX(),color.GetY(),color.GetZ());
	glBegin(GL_TRIANGLES);
		for (int i = 0; i < (int)faces.size(); i++) {
			Face& f = faces[i];

			Vector3d& v1 = verts[f.ids[0] - 1];
			Vector3d& v2 = verts[f.ids[1] - 1];
			Vector3d& v3 = verts[f.ids[2] - 1];

			Vector3d nf = (v2 - v1).normalize() % (v3 - v2).normalize();

			//glNormal3dv(nf);

			//glVertex3dv(v1);
			//glVertex3dv(v2);
			//glVertex3dv(v3);
			//glNormal3dv(nf);
			
			glNormal3d(nf.GetX(), nf.GetY(), nf.GetZ());
			glVertex3d(v1.GetX(), v1.GetY(), v1.GetZ());
			glVertex3d(v2.GetX(), v2.GetY(), v2.GetZ());
			glVertex3d(v3.GetX(), v3.GetY(), v3.GetZ());
			
		}
		glEnd();
	
		glPopMatrix();
}

/*
//front face
cout << "drawing front face" << endl;
glVertex3d(minPt.GetX(), minPt.GetY(), minPt.GetZ());
glVertex3d(maxPt.GetX(), minPt.GetY(), minPt.GetZ());
glVertex3d(maxPt.GetX(), maxPt.GetY(), minPt.GetZ());
glVertex3d(minPt.GetX(), maxPt.GetY(), minPt.GetZ());

//back face
cout << "drawing back face" << endl;
glVertex3d(minPt.GetX(), minPt.GetY(), maxPt.GetZ());
glVertex3d(maxPt.GetX(), minPt.GetY(), maxPt.GetZ());
glVertex3d(maxPt.GetX(), maxPt.GetY(), maxPt.GetZ());
glVertex3d(minPt.GetX(), maxPt.GetY(), maxPt.GetZ());

//top face
cout << "drawing top face" << endl;
glVertex3d(minPt.GetX(), maxPt.GetY(), minPt.GetZ());
glVertex3d(maxPt.GetX(), maxPt.GetY(), minPt.GetZ());
glVertex3d(maxPt.GetX(), maxPt.GetY(), maxPt.GetZ());
glVertex3d(minPt.GetX(), maxPt.GetY(), maxPt.GetZ());

//bottom face
cout << "drawing bottom face" << endl;
glVertex3d(minPt.GetX(), minPt.GetY(), minPt.GetZ());
glVertex3d(maxPt.GetX(), minPt.GetY(), minPt.GetZ());
glVertex3d(maxPt.GetX(), minPt.GetY(), maxPt.GetZ());
glVertex3d(minPt.GetX(), minPt.GetY(), maxPt.GetZ());

//side faces
cout << "drawing side faces" << endl;
glVertex3d(minPt.GetX(), minPt.GetY(), minPt.GetZ());
glVertex3d(minPt.GetX(), minPt.GetY(), maxPt.GetZ());
glVertex3d(minPt.GetX(), maxPt.GetY(), maxPt.GetZ());
glVertex3d(minPt.GetX(), maxPt.GetY(), minPt.GetZ());

glVertex3d(maxPt.GetX(), minPt.GetY(), minPt.GetZ());
glVertex3d(maxPt.GetX(), minPt.GetY(), maxPt.GetZ());
glVertex3d(maxPt.GetX(), maxPt.GetY(), maxPt.GetZ());
glVertex3d(maxPt.GetX(), maxPt.GetY(), minPt.GetZ());
*/