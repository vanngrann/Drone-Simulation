#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "Vector.h"
using namespace mathtool;
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Cell3D {
public:
	Cell3D();
	void Init(int _i, int _j, int _k, Vector3d _center, double _dx, double _dy, double _dz, bool _blocked);
	void Draw3D();
	Vector3d GetCenter() { return center; }
	bool IsCollision(Vector3d p, double radius);

	void saveEnv();

	void EdgeCheck3D(Vector3d p, double radius, bool& flipX, bool& flipY, bool&flipZ, double& txmin, double& txmax, double& tymin, double& tymax, double& tzmin, double& tzmax, int& xcondition, int& ycondition, int& zcondition);

	int xi;
	int xj;
	int xk;
	double dx;
	double dy;
	double dz;
	Vector3d center;
	Vector3d minPt;
	Vector3d maxPt;
	bool blocked;
	bool isCol;
	//for finding path
	double tentativeDist;
	//	tuple<int, int, int> parent;
	bool visited;
};
const int X = 2;
const int Y = 2;
const int Z = 2;

class Environment3D {
public:
	Environment3D();
	Environment3D(string _inputFile, double _xmin, double _xmax, double _ymin, double _ymax, double _zmin, double _zmax);
	void Draw3D();

	void saveEnv3D();

	tuple<int, int, int> GetCellIndices(Vector3d p);
	//	tuple<int, int, int> GetClosestBlocked(tuple<int, int, int> curCellInd, Vector3d pos, double radius);
	//	Vector3d GetWrappedPosition(Vector3d p, bool& updated);
	//Vector3d GetValidPosition(Vector3d p, Vector3d oldP, double radius, Vector3d& vel, bool& updated);
	//	Vector3d GetValidPosition2(Vector3d p, Vector3d oldP, double radius, Vector3d& vel, bool& updated);
	void MakeEmptyEnv();

	void FindPathToRandomFreeCell(Vector3d p, vector< tuple<int, int, int> >& cellPath);
	void DijkstrasFindPath(tuple<int, int, int> curCellInd, tuple<int, int, int> goalCellInd, vector< tuple<int, int, int> >& cellPath);
	void ResetCellValues();


	void ToggleBlockedCell3D(double tx, double ty, double tz);

	//Cell3D*** cells3D;
	Cell3D cells3D[X][Y][Z];

	double xmin, xmax, ymin, ymax, zmin, zmax;
	double dx, dy, dz;

	string inputFile;
	bool initialized;
};

#endif