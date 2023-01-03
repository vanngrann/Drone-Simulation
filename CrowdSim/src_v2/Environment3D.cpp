#ifndef MACOS
#include <windows.h>
#pragma comment(lib, "user32.lib") 
#endif

#include "Environment3D.h"
#include "Environment.h"
#include <fstream>
#include <tuple>

#include <GL/glut.h>  // (or others, depending on the system in use)

bool envDebug3D = false; //true;//false;
extern vector <Vector3d> destinationPts;
extern vector<pair<int, int>> destination3D;
extern int jobIndex3D;
extern int jobIndex;
int maxJobIndex;
extern bool release;
bool removeDrone = true;

Cell3D::Cell3D()
{
//	cout << "default constructer" << endl;
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
	glLineWidth(3);
	glColor3f(0.0, 0.0, 0.0);

	if (blocked) {
		glBegin(GL_LINE_LOOP);
		glVertex3d(minPt.GetX(), minPt.GetY(), minPt.GetZ());
		glVertex3d(maxPt.GetX(), minPt.GetY(), minPt.GetZ());
		glVertex3d(maxPt.GetX(), maxPt.GetY(), minPt.GetZ());
		glVertex3d(minPt.GetX(), maxPt.GetY(), minPt.GetZ());
		glEnd();

	}

	//front face
////	cout << "drawing front face" << endl;
//	glVertex3d(minPt.GetX(), minPt.GetY(), minPt.GetZ());
//	glVertex3d(maxPt.GetX(), minPt.GetY(), minPt.GetZ());
//	glVertex3d(maxPt.GetX(), maxPt.GetY(), minPt.GetZ());
//	glVertex3d(minPt.GetX(), maxPt.GetY(), minPt.GetZ());
//
//	//back face
////	cout << "drawing back face" << endl;
//	glVertex3d(minPt.GetX(), minPt.GetY(), maxPt.GetZ());
//	glVertex3d(maxPt.GetX(), minPt.GetY(), maxPt.GetZ());
//	glVertex3d(maxPt.GetX(), maxPt.GetY(), maxPt.GetZ());
//	glVertex3d(minPt.GetX(), maxPt.GetY(), maxPt.GetZ());
//
//	//top face
////	cout << "drawing top face" << endl;
//	glVertex3d(minPt.GetX(), maxPt.GetY(), minPt.GetZ());
//	glVertex3d(maxPt.GetX(), maxPt.GetY(), minPt.GetZ());
//	glVertex3d(maxPt.GetX(), maxPt.GetY(), maxPt.GetZ());
//	glVertex3d(minPt.GetX(), maxPt.GetY(), maxPt.GetZ());
//
//	//bottom face
////	cout << "drawing bottom face" << endl;
//	glVertex3d(minPt.GetX(), minPt.GetY(), minPt.GetZ());
//	glVertex3d(maxPt.GetX(), minPt.GetY(), minPt.GetZ());
//	glVertex3d(maxPt.GetX(), minPt.GetY(), maxPt.GetZ());
//	glVertex3d(minPt.GetX(), minPt.GetY(), maxPt.GetZ());
//
//	//side faces
////	cout << "drawing side faces" << endl;
//	glVertex3d(minPt.GetX(), minPt.GetY(), minPt.GetZ());
//	glVertex3d(minPt.GetX(), minPt.GetY(), maxPt.GetZ());
//	glVertex3d(minPt.GetX(), maxPt.GetY(), maxPt.GetZ());
//	glVertex3d(minPt.GetX(), maxPt.GetY(), minPt.GetZ());
//
//	glVertex3d(maxPt.GetX(), minPt.GetY(), minPt.GetZ());
//	glVertex3d(maxPt.GetX(), minPt.GetY(), maxPt.GetZ());
//	glVertex3d(maxPt.GetX(), maxPt.GetY(), maxPt.GetZ());
//	glVertex3d(maxPt.GetX(), maxPt.GetY(), minPt.GetZ());
	glBegin(GL_LINE_LOOP);
	glVertex3d(minPt.GetX(), minPt.GetY(), minPt.GetZ());
	glVertex3d(maxPt.GetX(), minPt.GetY(), minPt.GetZ());
	glVertex3d(maxPt.GetX(), maxPt.GetY(), minPt.GetZ());
	glVertex3d(minPt.GetX(), maxPt.GetY(), minPt.GetZ());

	glVertex3d(minPt.GetX(), minPt.GetY(), minPt.GetZ());
	glVertex3d(minPt.GetX(), minPt.GetY(), maxPt.GetZ());
	glVertex3d(minPt.GetX(), maxPt.GetY(), maxPt.GetZ());
	glVertex3d(minPt.GetX(), maxPt.GetY(), minPt.GetZ());

	glVertex3d(minPt.GetX(), maxPt.GetY(), maxPt.GetZ());
	glVertex3d(maxPt.GetX(), maxPt.GetY(), maxPt.GetZ());
	glVertex3d(maxPt.GetX(), minPt.GetY(), maxPt.GetZ());
	glVertex3d(minPt.GetX(), minPt.GetY(), maxPt.GetZ());

	glVertex3d(maxPt.GetX(), minPt.GetY(), maxPt.GetZ());
	glVertex3d(maxPt.GetX(), minPt.GetY(), minPt.GetZ());
	glVertex3d(maxPt.GetX(), maxPt.GetY(), minPt.GetZ());

	glVertex3d(maxPt.GetX(), maxPt.GetY(), maxPt.GetZ());
	glVertex3d(maxPt.GetX(), minPt.GetY(), maxPt.GetZ());
	glVertex3d(maxPt.GetX(), minPt.GetY(), minPt.GetZ());


	glEnd();
}

Environment3D::Environment3D(double _xmin, double _xmax, double _ymin, double _ymax, double _zmin, double _zmax) {
	//inputFile = _inputFile;

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

//	cout << dx << ' ' << dy << ' ' << dz << endl;

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
//				cout << X << endl;
			}
		}
	}
}

void Environment3D::ToggleBlockedCell3D(double tx, double ty, double tz) {
	Vector3d p(tx, ty, tz);
	tuple<int, int, int> cellInd = GetCellIndices3D(p);
	cout << "Cell indices = " << get<0>(cellInd) << "," << get<1>(cellInd) << "," << get<2>(cellInd) << endl;
	cells3D[get<0>(cellInd)][get<1>(cellInd)][get<2>(cellInd)].blocked = !cells3D[get<0>(cellInd)][get<1>(cellInd)][get<2>(cellInd)].blocked;
}

void Environment3D::FindPathToRandomFreeCell3D(Vector3d p, vector< tuple<int, int, int> >& cellPath) {
	
	//find the grid cell p is in
	tuple<int, int, int> curCellInd3D = GetCellIndices3D(p);
	if (cells3D[get<0>(curCellInd3D)][get<1>(curCellInd3D)][get<2>(curCellInd3D)].blocked) {
		cout << "Attempting to create path from a blocked cell!!! Returning. " << endl;
		return;
	}
	//find a random grid cell
	bool inBlockedCell = false;
	jobIndex3D++;

	if (jobIndex3D >= destination3D.size()) jobIndex3D = 0;
	

	maxJobIndex = jobIndex3D;

	cout << "jobIndex Drone = " << jobIndex3D << endl << "destination3D: (" << destination3D[jobIndex3D].first << ", " << destination3D[jobIndex3D].second << ")" << endl;


	int r_i = 0;
	int r_j = destination3D[jobIndex3D].first;
	int r_k = destination3D[jobIndex3D].second;

	//do {

	//	//	  r_i = 4 + rand() % 5;
	//	//	  r_j = 4 + rand() % 15;
	//	r_i = rand() % X;
	//	r_j = rand() % Y;
	//	r_k = rand() % Z;
	//	inBlockedCell = cells3D[r_i][r_j][r_k].blocked;
	//} while (inBlockedCell);
	//call find path from grid cell to grid cell
	cellPath.clear();

	if (envDebug3D) cout << "Finding path from curCellInd: " << get<0>(curCellInd3D) << "," << get<1>(curCellInd3D) << "," << get<2>(curCellInd3D) <<  " to goalCell: " << r_i << "," << r_j << "," << r_k << endl;

//	tuple<int, int, int> newTuple = make_tuple(1, 2, 3);

//	DijkstrasFindPath3D(curCellInd3D, newTuple, cellPath); //make_tuple(r_i, r_j, r_k)
	DijkstrasFindPath3D(curCellInd3D, make_tuple(r_i, r_j, r_k), cellPath); //make_tuple(r_i, r_j, r_k)

	if (1 && envDebug3D) {
		cout << "Path Found: ";
		for (int i = 0; i<cellPath.size(); i++) {
			cout << "(" << i << ") [ " << get<0>(cellPath[i]) << "," << get<1>(cellPath[i]) << "," << get<2>(cellPath[i]) << "] ";
		}
		cout << endl;
	}
//	jobIndex3D++;
}

tuple<int, int, int> Environment3D::GetClosestBlocked3D(tuple<int, int, int> curCellInd, Vector3d pos, double radius) {
	int numXToOffset = int(dx / radius + 0.5) + 1;
	int numYToOffset = int(dy / radius + 0.5) + 1;
	int numZToOffset = int(dz / radius + 0.5) + 1;
	int zIndexStart = get<2>(curCellInd) - numZToOffset;
	int xIndexStart = get<1>(curCellInd) - numXToOffset;
	int yIndexStart = get<0>(curCellInd) - numYToOffset;
	if (xIndexStart < 0) xIndexStart = 0;
	if (yIndexStart < 0) yIndexStart = 0;
	if (zIndexStart < 0) zIndexStart = 0;
	int zIndexEnd = get<2>(curCellInd) + numZToOffset;
	int xIndexEnd = get<1>(curCellInd) + numXToOffset;
	int yIndexEnd = get<0>(curCellInd) + numYToOffset;
	if (xIndexEnd >= (Y)) xIndexEnd = Y - 1;
	if (yIndexEnd >= (X)) yIndexEnd = X - 1;
	if (zIndexEnd >= (Z)) zIndexEnd = Z - 1;
	if (envDebug3D)cout << "GetClosestBlocked xStart " << xIndexStart << " xEnd " << xIndexEnd << " yStart " << yIndexStart << " yEnd " << yIndexEnd << " zStart " << zIndexStart << " zEnd " << zIndexEnd << " nRows " << X << " nColumns " << Y << " zColumns " << Z << endl;
	tuple<int, int, int> closestCellIndex(-1, -1, -1);
	double closeDist = 1e6;
	for (int i = yIndexStart; i <= yIndexEnd; i++) {
		for (int j = xIndexStart; j <= xIndexEnd; j++) {
			for (int k = zIndexStart; k <= zIndexEnd; k++) {
				if (envDebug3D) cout << " checking cell i,j: [" << i << "," << j << "," << k <<"]" << endl;
				if (cells3D[i][j][k].blocked) {
					double dist = (cells3D[i][j][k].GetCenter() - pos).norm();
					if (dist < closeDist) {
						closeDist = dist;
						closestCellIndex = make_tuple(i, j, k);
					}
				}
			}//endfor k
		}//endfor j
	}//endfor i
	return closestCellIndex;
}

int countPath2 = 1;

void Environment3D::DijkstrasFindPath3D(tuple<int, int, int> curCellInd, tuple<int, int, int> goalCellInd, vector< tuple<int, int, int> >& cellPath) {
	ResetCellValues3D();
	cells3D[get<0>(curCellInd)][get<1>(curCellInd)][get<2>(curCellInd)].visited = true;
	cells3D[get<0>(curCellInd)][get<1>(curCellInd)][get<2>(curCellInd)].tentativeDist = 0;
	vector<Cell3D*> unvisited;
	unvisited.push_back(&cells3D[get<0>(curCellInd)][get<1>(curCellInd)][get<2>(curCellInd)]);
	bool foundPath = false;
	while (!foundPath && !unvisited.empty()) {
		Cell3D* cur = unvisited[0];
		unvisited.erase(unvisited.begin());
		if (cur->xi == get<0>(goalCellInd) && cur->xj == get<1>(goalCellInd) && cur->xk == get<2>(goalCellInd)) {
			foundPath = true;
		}
		else {
			//foreach neighbor - add to unvisited with new tentative distance
			for (int i = cur->xi - 1; i <= cur->xi + 1; i++) {
				for (int j = cur->xj - 1; j <= cur->xj + 1; j++) {
					for (int k = cur->xk - 1; k <= cur->xk + 1; k++) {

						if (i == cur->xi && j == cur->xj && k == cur->xk) continue; //this will be cur node
						if (i < 0 || i >= X) continue; //out of bounds
						if (j < 0 || j >= Y) continue; //out of bounds
						if (k < 0 || j >= Z) continue; //out of bounds
						if (cells3D[i][j][k].blocked) continue;//don't add blocked cells

						if (i != cur->xi && j != cur->xj && k != cur->xk) { //disallow diagonal moves in certain cases
							if (cells3D[cur->xi][j][k].blocked) continue;
							if (cells3D[i][cur->xj][k].blocked) continue;
							if (cells3D[i][j][cur->xk].blocked) continue;
						}
						/*
						if( i<cur->xi && j<cur->xj ) { //disallow diagonal moves in certain cases
						if( cells[cur->xi][j].blocked ) continue;
						if( cells[i][cur->xj].blocked ) continue;
						}
						if( i<cur->xi && j>cur->xj ) { //disallow diagonal moves in certain cases
						if( cells[cur->xi][j].blocked ) continue;
						if( cells[i][cur->xj].blocked ) continue;
						}
						if( i>cur->xi && j<cur->xj ) { //disallow diagonal moves in certain cases
						if( cells[cur->xi][j].blocked ) continue;
						if( cells[i][cur->xj].blocked ) continue;
						}
						*/
						double ijkTentativeDist = cur->tentativeDist + (cur->center - cells3D[i][j][k].center).norm();
						if (ijkTentativeDist < cells3D[i][j][k].tentativeDist) {
							//add to unvisited...also save parent
							cells3D[i][j][k].parent3D = make_tuple(cur->xi, cur->xj, cur->xk);
							cells3D[i][j][k].tentativeDist = ijkTentativeDist;
							unvisited.push_back(&cells3D[i][j][k]);
						}
					}//endfor k
				}//endfor j
			}//endfor i
		}
	}//endwhile

	if (foundPath) {
		//backtrack
//		countPath2++;
		cout << "Path found for drone" << endl;
//		if(countPath2 % 2 == 1) removeDrone = true;

		removeDrone = true;

		tuple<int, int, int> curBackTrackCell = goalCellInd;
		while (!((get<0>(curBackTrackCell) == get<0>(curCellInd) &&
			(get<1>(curBackTrackCell) == get<1>(curCellInd)) && (get<2>(curBackTrackCell) == get<2>(curCellInd))))) {
			cellPath.push_back(curBackTrackCell);
			curBackTrackCell = cells3D[get<0>(curBackTrackCell)][get<1>(curBackTrackCell)][get<2>(curBackTrackCell)].parent3D;
		}//endwhile
		cellPath.push_back(curBackTrackCell);

	}

}

void Environment3D::ResetCellValues3D() {
	for (int i = 0; i<X; i++) {
		for (int j = 0; j<Y; j++) {
			for (int k = 0; k < Z; k++) {
				cells3D[i][j][k].tentativeDist = 1e7;
				cells3D[i][j][k].parent3D = make_tuple(-1, -1, -1);
				cells3D[i][j][k].visited = false;
			}
		}
	}
}

tuple<int, int, int> Environment3D::GetCellIndices3D(Vector3d p) {
	if (envDebug3D) cout << "Env::GCI p= " << p << " [" << xmin << "," << xmax << "|" << ymin << "," << ymax << "|" << zmin << "," << zmax << "] dx=" << dx << " dy=" << dy << " dz=" << dz << endl;
	int j = int((p[0] - xmin) / dx);
	int i = int((p[1] - ymin) / dy);
	int k = int((p[2] - zmin) / dz);
	//cout << "1i " << int((p[0]-xmin)/(xmax-xmin)) << " j " << j << endl;
	if (i<0) i = 0;
	if (j<0) j = 0;
	if (k<0) k = 0;
	if (k >= Z) k = Z - 1;
	if (j >= Y) j = Y - 1;
	if (i >= X) i = X - 1;
	//cout << "2i " << i << " j " << j << endl;
	return make_tuple(i, j, k);
}