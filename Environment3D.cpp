#ifndef MACOS
#include <windows.h>
#pragma comment(lib, "user32.lib") 
#endif

#include "Environment3D.h"
#include <fstream>

#include <GL/glut.h>  // (or others, depending on the system in use)

Cell3D::Cell3D()
{
	cout << "default constructer" << endl;
	xi = -1;
	xj = -1;
	xk = -1;
}

void Cell3D::Init(int _i, int _j, int _k, Vector3d _center, double _dx, double _dy, double _dz, bool _blocked) {
	xi = _i;
	xj = _j;
	xk = _k;
	dx = _dx;
	dy = _dy;
	dz = _dz;
	center = _center;
	//minPt[0] = center[0] - dx / 2.0;
	//minPt[1] = center[1] - dy / 2.0;
	//minPt[2] = center[2] - dz / 2.0;
	//maxPt[0] = center[0] + dx / 2.0;
	//maxPt[1] = center[1] + dy / 2.0;
	//maxPt[2] = center[2] + dz / 2.0;

//	Vector3d set;
	minPt.SetX(center.GetX() - dx / 2.0);
	minPt.SetY(center.GetY() - dy / 2.0);
	minPt.SetZ(center.GetZ() - dz / 2.0);
	maxPt.SetX(center.GetX() + dx / 2.0);
	maxPt.SetY(center.GetY() + dy / 2.0);
	maxPt.SetZ(center.GetZ() + dz / 2.0);

	blocked = _blocked;
	isCol = false;
}

void Cell3D::Draw3D()
{
	//cout << "drawing in cell 3D" << endl;
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	
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

	glEnd();
}

Environment3D::Environment3D(string _inputFile, double _xmin, double _xmax, double _ymin, double _ymax, double _zmin, double _zmax) {
	inputFile = _inputFile;

	xmin = _xmin;
	xmax = _xmax;
	ymin = _ymin;
	ymax = _ymax;
	zmin = _zmin;
	zmax = _zmax;

	//	cout << " Environment boundaries: [" << xmin << ", " << xmax << " | " << ymin << ", " << ymax << "]" << endl;

	//cout << "Attempting to load environment file: " << inputFile << endl;
	//ifstream infile;
	//infile.open(inputFile.c_str());
	//if (!infile) {
	//	cout << "Could NOT open infile: " << inputFile << endl;
	//	//exit(-1);
	//}
	//if (infile >> x) {
	//	cout << "There will be " << x << " rows ";
	//}
	//if (infile >> y) {
	//	cout << "There will be " << y << " rows ";
	//}

	//for (int i = 0; i < x; i++) {
	//	for (int j = 0; j < y; j++)
	//	{
	//		cells3D[j] = new Cell3D[z];
	//	}
	//}

	dx = (_xmax - _xmin) / Y;
	dy = (_ymax - _ymin) / X;
	dz = (_zmax - _zmin) / Z;

	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			for (int k = 0; k < Z; k++)
			{
				Cell3D& cell = cells3D[i][j][k];
				//bool isBlocked = (colData.at(j) == 'x' || colData.at(j) == 'X') ? true : false;
				Vector3d center(xmin + dx / 2 + dx*j, ymin + dy / 2 + dy*i, zmin + dz / 2 + dz * k);
				cell.Init(i, j, k, center, dx, dy, dz, false);
			}
		}
	}

	
	//string tmpStr;
	//getline(infile, tmpStr); //just to get rid of carriage return
	//int rowIndex = 0;
	//while (getline(infile, colData)) {
	//	//cout << rowIndex << " going to process '"<<colData<<"'"<<endl;
	//	for (int j = 0; j<(int)colData.length(); j++) {
	//		Cell3D& cell = cells3D[rowIndex][j];

	//		bool isBlocked = (colData.at(j) == 'x' || colData.at(j) == 'X') ? true : false;
	//		Vector3d center(xmin + dx / 2 + dx*j, ymin + dy / 2 + dy*rowIndex, zmin + dz / 2 + dz *);
	//		//cout << "Initializing cell: " << rowIndex << ", " << i << " center: " << center.GetX() << " " << center.GetY() << " dx " << dx << " dy " << dy << " isBlocked " << isBlocked << endl;
	//		cell.Init(rowIndex, j, k, center, dx, dy, isBlocked);
	//	}
	//	rowIndex++;
	//}



//	infile.close();
	initialized = true;
}

Environment3D::Environment3D() {
	initialized = false;
}

void Environment3D::Draw3D() {
	if (!initialized) return;
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			for (int k = 0; k < Z; k++)
			{
				cells3D[i][j][k].Draw3D();
			}
		}
	}
}