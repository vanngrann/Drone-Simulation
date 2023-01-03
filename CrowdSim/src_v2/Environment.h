#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "Vector.h"
using namespace mathtool;
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Cell {
public:
  Cell();
  void Init(int _i, int _j, Vector3d _center, double _dx, double _dy, bool _blocked);
  void Draw();
  Vector3d GetCenter() { return Vector3d(center.GetX(),center.GetY(),0); }
  bool IsCollision(Vector3d p, double radius);

  void saveEnv();

  //this function will set maximums for the cell and return values
  //like whether or not the x/y is in collision, the
  //min/max values, and which condition is violated
  void EdgeCheck(Vector3d p, double radius, bool& flipX, bool& flipY, double& txmin, double& txmax, double& tymin, double& tymax, int& xcondition, int& ycondition);

  int xi;
  int xj;
  double dx;
  double dy;
  Vector3d center;
  Vector3d minPt;
  Vector3d maxPt;
  bool blocked;
  bool isCol;
  //for finding path
  double tentativeDist;
  pair<int,int> parent;
  bool visited;
};

class Environment {
public:
  Environment();
  Environment(string _inputFile, double _xmin, double _xmax, double _ymin, double _ymax );
  void PathDestination(string _inputFile);
  void Draw();

  void saveEnv();

  pair<int,int> GetCellIndices(Vector3d p);
  pair<int,int> GetClosestBlocked(pair<int,int> curCellInd, Vector3d pos, double radius);
  Vector3d GetWrappedPosition(Vector3d p, bool& updated);
  //Vector3d GetValidPosition(Vector3d p, Vector3d oldP, double radius, Vector3d& vel, bool& updated);
  Vector3d GetValidPosition2(Vector3d p, Vector3d oldP, double radius, Vector3d& vel, bool& updated);
  void MakeEmptyEnv();

  void FindPathToRandomFreeCell(Vector3d p, vector< pair<int,int> >& cellPath);
  void DijkstrasFindPath(pair<int,int> curCellInd, pair<int,int> goalCellInd, vector< pair<int,int> >& cellPath); 
  void ResetCellValues();


  void ToggleBlockedCell(double tx, double ty);

  Cell** cells;

  double xmin, xmax, ymin, ymax; 
  double dx, dy;
  int rows, columns;

  int jobs;
  int jobIndex;
  vector<int> time;
  vector<pair<int, int>> destination;
  string inputFile;
  bool initialized;
};

#endif
