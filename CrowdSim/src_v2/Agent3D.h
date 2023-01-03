#ifndef AGENT3D
#define AGENT3D
#include "Vector.h"
using namespace mathtool;
#include <vector>
#include <GL/glut.h>
#include <tuple>
using namespace std;

//#include "cal3dmodel.h"

class Agent3D {
public:
	Agent3D();
	Agent3D(const Agent3D& other);

	void Init3D(int _id, Vector3d _pos, Vector3d _vel, double _mass, double _maxVel, double _maxAccel, double _viewRadius);
	Vector3d& GetPos() { return pos; }
	Vector3d& GetVel() { return vel; }
	double GetRadius() { return radius; }
	int GetID() { return id; }


	void Update3D(vector<Agent3D>& agents, double dt);
	void UpdateNew(vector<Agent3D>& agents, double dt);
	void ResolveCollisionWithOtherAgents(vector<Agent3D>& agents);
	void Draw3D();

	//////////////////////////////////////////////////////////////////////
	// cal3d model for drawing moving models
//	bool InitCal3dModel(string _cal3dDataPath, string _cal3dModel,
//		tuple<double, double, double> cal3dRunS,
//		tuple<double, double, double> cal3dWalkS,
//		tuple<double, double, double> cal3dWaitS,
//		double animation_speed, double scale_factor);
////	void UpdateCal3d(double vel, string tag);
////	Cal3dModel* m_Cal3dModel;
////	string m_strDatapath;
////	std::string m_strCal3D_Datapath;
//	tuple<double, double, double> m_Cal3dRunSpeed;
//	tuple<double, double, double> m_Cal3dWalkSpeed;
//	tuple<double, double, double> m_Cal3dWaitSpeed;
//	double m_Cal3dScaleFactor;
//	double m_Cal3dAnimationSpeed;
//	bool m_DoCal3d;
//	float motionBlend[3];
//	bool cal3dInitialized;
//
//	///////-------------------------
//	//tuple<double, double, double> m_cal3dRunSpeed;   
//	//tuple<double, double, double> m_cal3dWalkSpeed;  
//	//tuple<double, double, double> m_cal3dWaitSpeed;  
//	double m_cal3dAnimationSpeed;
//	double m_cal3dScaleFactor;
	/////////////////////////////////////////////////////////////////////
	GLUquadric* qobj; //for drawing simple sphere
					  /////////////////////////////////////////////////////////////////////

private:
	int id;
	Vector3d pos, oldPos;
	Vector3d vel;
	double ori;
	//Vector3d accel;
	Vector3d separationForce;
	Vector3d cohesionForce;
	Vector3d alignmentForce;

	double separationComponent;
	double cohesionComponent;
	double alignmentComponent;
	double pathComponent;

	double radius;
	double mass;
	double maxVel;
	double maxAccel;
	double viewRadius;

	bool initialized;

	tuple<int, int, int> gridCell3D;

	bool drawForce;
	bool drawVelocity;
	bool drawVR;

	//path
//	vector< pair<int, int> > pathCells;
	vector < tuple<int, int, int> >pathCells3D;

};
#endif