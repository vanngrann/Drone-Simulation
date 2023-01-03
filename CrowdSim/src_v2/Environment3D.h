#ifndef ENVIRONMENT3D
#define ENVIRONMENT3D

#include "Vector.h"
using namespace mathtool;
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
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
	tuple<int, int, int> parent3D;
	bool blocked;
	bool isCol;
	//for finding path
	double tentativeDist;
	//	tuple<int, int, int> parent;
	bool visited;
};
const int X = 5;
const int Y = 5;
const int Z = 5;

class Environment3D {
public:
	Environment3D();
	Environment3D(double _xmin, double _xmax, double _ymin, double _ymax, double _zmin, double _zmax);
	void Draw3D();

	void saveEnv3D();
	
//	tuple<int, int, int> pairs;

	tuple<int, int, int> GetCellIndices3D(Vector3d p);
	//	tuple<int, int, int> GetClosestBlocked(tuple<int, int, int> curCellInd, Vector3d pos, double radius);
	//	Vector3d GetWrappedPosition(Vector3d p, bool& updated);
	//Vector3d GetValidPosition(Vector3d p, Vector3d oldP, double radius, Vector3d& vel, bool& updated);
	//	Vector3d GetValidPosition2(Vector3d p, Vector3d oldP, double radius, Vector3d& vel, bool& updated);
	void MakeEmptyEnv();

	void FindPathToRandomFreeCell3D(Vector3d p, vector< tuple<int, int, int> >& cellPath);
	void DijkstrasFindPath3D(tuple<int, int, int> curCellInd, tuple<int, int, int> goalCellInd, vector< tuple<int, int, int> >& cellPath);
	void ResetCellValues3D();
	tuple<int, int, int> GetClosestBlocked3D(tuple<int, int, int> curCellInd, Vector3d pos, double radius);


	void ToggleBlockedCell3D(double tx, double ty, double tz);

	//Cell3D*** cells3D;
	Cell3D cells3D[X][Y][Z];

	double xmin, xmax, ymin, ymax, zmin, zmax;
	double dx, dy, dz;


	string inputFile;
	bool initialized;
};

#endif