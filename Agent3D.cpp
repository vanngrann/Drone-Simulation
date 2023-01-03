#ifndef MACOS
#include <windows.h>
#pragma comment(lib, "user32.lib") 
#endif

#include "Environment3D.h"
#include "Agent3D.h"
#include <tuple>

#include <GL/glut.h>  // (or others, depending on the system in use)
bool agDebug3D = false; //true;//false;//true;
//bool m_Cal3DDebug = false;

//extern Environment* gEnv;
extern Environment3D* gEnv3D;

extern bool doSkeletalAnimation;

Agent3D::Agent3D() {
	initialized = false;
	drawForce = true;
	drawVelocity = true;
	drawVR = false;
//	qobj = NULL;
} //empty constructor

void Agent3D::Init3D(int _id, Vector3d _pos, Vector3d _vel, double _mass,
	double _maxVel, double _maxAccel, double _viewRadius) {
	initialized = true;
	id = _id;
	pos = _pos;
	vel = _vel;
	mass = _mass;
	maxVel = _maxVel;
	maxAccel = _maxAccel;
	viewRadius = _viewRadius;
	ori = 0;
	radius = 5;

	drawForce = true;
	drawVelocity = true;
	drawVR = false;

	separationComponent = 10;
	cohesionComponent = 10;
	alignmentComponent = 10;
	pathComponent = 100;
//	cal3dInitialized = false;
//	qobj = NULL;
}

Agent3D::Agent3D(const Agent3D& other) {
	initialized = other.initialized;
	id = other.id;
	pos = other.pos;
	vel = other.vel;
	separationComponent = other.separationComponent;
	cohesionComponent = other.cohesionComponent;
	alignmentComponent = other.alignmentComponent;
	pathComponent = other.pathComponent;
	radius = other.radius;
	mass = other.mass;
	maxVel = other.maxVel;
	maxAccel = other.maxAccel;
	viewRadius = other.viewRadius;
	gridCell3D = other.gridCell3D;
	drawForce = other.drawForce;
	drawVelocity = other.drawVelocity;
	drawVR = other.drawVR;
	ori = other.ori;
//	cal3dInitialized = false;
//	qobj = NULL;
}

void Agent3D::Update3D(vector<Agent3D>& agents, double dt) {
	if (!initialized) {
		cout << "Agent::Update id: " << id << " HAS NOT BEEN INITIALIZED> " << endl;
		exit(-1);
	}
//	if (!cal3dInitialized && doSkeletalAnimation) {
//		cout << "Agent::cal3d Not Initialized! id: " << id << "...initializing." << endl;
//		//vector<string> models = getTagsFromString(m_cal3dmodelAnims, ",");
//		//int rindex = lrand48() % models.size();
//		string m_cal3dmodelPath = "";// "cal3ddata/simpleman_costumes2/";
//									 //string selected_model = "simple-man.cfg";//models[rindex];
//		string selected_model = "";// "simple-man_blue&medium.cfg";
////		setAgentValues(m_cal3dmodelPath, selected_model);
//		string full_model = m_cal3dmodelPath + selected_model;
//		m_Cal3dRunSpeed = make_pair(9.0, 1.0);
//		m_Cal3dWalkSpeed = make_pair(2.0, 1.0);
//		m_Cal3dWaitSpeed = make_pair(0.2, 0.8);
//		m_cal3dAnimationSpeed = 0.01;
//		m_cal3dScaleFactor = 0.15;
//		//m_cal3dScaleFactor = 0.45;
//		InitCal3dModel(m_cal3dmodelPath, full_model, m_Cal3dRunSpeed, m_Cal3dWalkSpeed, m_Cal3dWaitSpeed, m_cal3dAnimationSpeed, m_cal3dScaleFactor);
//		cal3dInitialized = true;
//	}

	//////////////////////////////////////////////////////////////////
	//find simple path
	Vector3d pathForce(0, 0, 0);

	if (pathCells3D.empty()) {
		if (agDebug3D) cout << "Calling FindPathToRandomFreeCell!" << endl;
//		gEnv3D->FindPathToRandomFreeCell3D(pos, pathCells3D);
	}
	else {
		//grab the last cell's center, generate a force in that direction
		int pathIndex = pathCells3D.size() - 1;
		tuple<int, int, int> cellIndex = pathCells3D[pathIndex];
		Vector3d& goalLoc = gEnv3D->cells3D[get<0>(cellIndex)][get<1>(cellIndex)][get<2>(cellIndex)].center;///////////////////////////////////
		//create a force in that direction
		pathForce = goalLoc - pos;
		double mag = pathForce.norm();
		if (mag > pathComponent) {
			pathForce.selfScale(pathComponent);
		}
		//if distance is small pop it off
		if (mag < 5) { //pop off
			pathCells3D.pop_back();
		}
	}
	//////////////////////////////////////////////////////////////////

	//double separationComponent = 240;
	Vector3d separation(0, 0, 0);
	Vector3d cohesion(0, 0, 0);
	Vector3d alignment(0, 0, 0);
	Vector3d center(0, 0, 0);
	Vector3d force(0, 0, 0);
	separationForce.reset();
	cohesionForce.reset();
	alignmentForce.reset();
	int numSeen = 0;
	if (agDebug3D) cout << "Update for agent: " << id << endl;
	//generate the forces
	for (int i = 0; i<(int)agents.size(); i++) {
		if (id == i) continue; //skip self
							   //see if within view radius
		double dist = (agents[i].GetPos() - pos).norm();
		if (dist < viewRadius) {
			if (agDebug3D) cout << "Agent: " << id << " is within range of agent: " << i << " dist= " << dist << " viewRadius= " << viewRadius << endl;
			if (agDebug3D) cout << "SEPDBG agent[" << i << "].GetPos() " << agents[i].GetPos() << " pos[" << id << "]" << pos << endl;
			if (agDebug3D) cout << "SEPDBG agent[" << i << "]: separation component: " << agents[i].GetPos() - pos << endl;
			//separation += (agents[i].GetPos()-pos).normalize()*(1.0-dist/viewRadius);
			separation += (pos - agents[i].GetPos()).normalize()*(1.0 - dist / viewRadius);
			center += agents[i].GetPos();
			alignment += agents[i].GetVel();
			numSeen++;
		}
	}//endfor i

	if (numSeen>0) {
		center /= 1.0*numSeen;
		double distToCenter = (center - pos).norm();
		cohesion = (center - pos).normalize()*cohesionComponent*(distToCenter / viewRadius);
		//separation *= separationComponent;
		//alignment *= alignmentComponent;
		separation = separation.normalize() * separationComponent;
		alignment = alignment.normalize() * alignmentComponent;

		if (agDebug3D) cout << "component vectors for : " << id << endl;
		if (agDebug3D) cout << "sep " << separation << endl;
		if (agDebug3D) cout << "coh " << cohesion << endl;
		if (agDebug3D) cout << "ali " << alignment << endl;
		//force = separation + cohesion + alignment + pathForce;
		force = separation + pathForce;
		if (force.norm()>maxAccel) force.selfScale(maxAccel);
		separationForce = separation;
		cohesionForce = cohesion;
		alignmentForce = alignment;
		//force = separation;// + cohesion + alignment;
		if (agDebug3D) cout << "totalf " << force << endl;
		force /= mass;
	}
	else {
		if (agDebug3D) cout << "No agents visible for agent:  " << id << endl;
		force = pathForce;
	}
	if (agDebug3D) cout << "origPos " << pos << endl;
	if (agDebug3D) cout << "origVel " << vel << endl;
	oldPos = pos;
	pos = pos + vel*dt;
	vel = vel + force*dt;
	if (agDebug3D) cout << "newPos " << pos << endl;
	if (agDebug3D);
	double velMag = vel.norm();
	if (velMag > maxVel) {
		vel.selfScale(maxVel);
		velMag = maxVel;
	}
	if (0 && id<10) cout << id << " newVel " << vel << " mag: " << vel.norm() << " maxVel: " << maxVel << endl;
	if (velMag > 0.01) {
		ori = std::atan2(vel.GetX(), vel.GetY());//saved as radians
	}
	if (agDebug3D) cout << "newVel(trunc) " << vel << endl;

//	if (doSkeletalAnimation) UpdateCal3d(velMag, "");

/*	bool wrapWorld = false;
	if (wrapWorld) {
		bool updated = false;
		Vector3d pNew = gEnv3D->GetWrappedPosition(pos, updated);
		if (updated)
			pos = pNew;
	}

	bool cdWithAgents = true;
	if (cdWithAgents) {
		ResolveCollisionWithOtherAgents(agents);
	}

	bool cdWorld = true;
	if (cdWorld) {
		bool updated = false;
		//Vector3d pNew = gEnv->GetValidPosition(pos, oldPos, radius, vel, updated);
		Vector3d pNew = gEnv3D->GetValidPosition2(pos, oldPos, radius, vel, updated);
		if (updated) {
			if (agDebug3D) cout << "found a collision at pos: " << pos << ". resetting position to: " << pNew << endl;
			pos = pNew;
		}
	}
*/
}

void drawCircle3D(double radius, int divisions) {
	double deltaAng = TWOPI / divisions;
	double curAng = 0;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i<divisions; i++) {
		double x = radius * cos(curAng);
		double y = radius * sin(curAng);
		if (0 && agDebug3D) cout << "Circle " << i << " x= " << x << " y= " << y << endl;
		//glVertex2f( x, y );
		glVertex3f(x, 0, y);
		curAng += deltaAng;
		if (0 && agDebug3D) cout << "curAng= " << curAng << " deltaAng= " << deltaAng << endl;
	}
	glEnd();
}

void Agent3D::Draw3D() {
	glColor3f(0.2, 0.2, 0.8);
	glPushMatrix();
	glTranslatef(pos.GetX(), 0, pos.GetY());
	drawCircle3D(radius, 10);
	glPopMatrix();

	if (drawForce) {
		glColor3f(1.0, 0.48, 0.0);
		glBegin(GL_LINES);
		glVertex3f(pos.GetX(), 0, pos.GetY());
		glVertex3f(pos.GetX() + separationForce.GetX(), 0, pos.GetY() + separationForce.GetY());
		glEnd();

		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(pos.GetX(), 0, pos.GetY());
		glVertex3f(pos.GetX() + cohesionForce.GetX(), 0, pos.GetY() + cohesionForce.GetY());
		glEnd();

		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(pos.GetX(), 0, pos.GetY());
		glVertex3f(pos.GetX() + alignmentForce.GetX(), 0, pos.GetY() + alignmentForce.GetY());
		glEnd();
	}

	if (drawVelocity) {
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
		//glVertex2f(pos.GetX(), pos.GetY());
		//glVertex2f(pos.GetX() + vel.GetX(), pos.GetY() + vel.GetY());
		glVertex3f(pos.GetX(), 0, pos.GetY());
		glVertex3f(pos.GetX() + vel.GetX(), 0, pos.GetY() + vel.GetY());
		glEnd();
	}
	else { /*cout << "NO drawVelocity. " << endl;*/ }

	//draw path
	if (true && gEnv3D != NULL) {
		glColor3f(0, 0, 1);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < (int)pathCells3D.size(); i++) {
			tuple<int, int, int> cellIndex = pathCells3D[i];
			Vector3d& p = gEnv3D->cells3D[get<0>(cellIndex)][get<1>(cellIndex)][get<2>(cellIndex)].center;///////////////////////////////////
			glVertex3f(p.GetX(), p.GetY(), p.GetZ());
		}
		glEnd();
	}

	if (0){
		//doSkeletalAnimation && m_Cal3dModel && cal3dInitialized
		/*
		glPushMatrix();
		glTranslatef(pos.GetX(), 0, pos.GetY());
		double r[16] = { cos(ori), 0, -sin(ori), 0,
			0, 1, 0, 0,
			sin(ori), 0, cos(ori), 0,
			0, 0, 0, 1 };
		glMultMatrixd(r);
		glRotated(-90, 1, 0, 0);

		//draw cal3d model
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);

		glEnable(GL_DEPTH_TEST);
		//Vector3d color(0.9, 0.9, 0.9);
		Vector3d color(0.9, 0.09, 0.09);
		glColor3f(color.GetX(), color.GetY(), color.GetZ());
		glEnable(GL_NORMALIZE);
		glScaled(m_Cal3dScaleFactor, m_Cal3dScaleFactor, m_Cal3dScaleFactor);

		m_Cal3dModel->OnRender();


		glPopMatrix();*/
	}
	else {
		//draw cylinder
		//if (qobj == NULL) {
		//	cout << id << " Creating cylinder" << endl;
		//	qobj = gluNewQuadric();
		//	gluQuadricNormals(qobj, GLU_SMOOTH);
		//}
		/*void gluCylinder(GLUquadric*  	quad,
		GLdouble  	base,
		GLdouble  	top,
		GLdouble  	height,
		GLint  	slices,
		GLint  	stacks);*/
		//cout << id << " Drawing cylinder" << endl;
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		Vector3d color(0.9, 0.19, 0.39);
		glColor3f(color.GetX(), color.GetY(), color.GetZ());
		glColor3f(0.5, 0.5, 0.5);
		glEnable(GL_NORMALIZE);
		glPushMatrix();
		glTranslatef(pos.GetX(), pos.GetY(), pos.GetZ());
		/*
		double r[16] = { cos(ori), 0, -sin(ori), 0,
		0, 1, 0, 0,
		sin(ori), 0, cos(ori), 0,
		0, 0, 0, 1 };
		glMultMatrixd(r);
		*/
		glRotated(-90, 1, 0, 0);

		//	  gluCylinder(qobj, radius, radius, 4, 8, 16);
//		gluCylinder(qobj, radius, 2, 10, 8, 16);
		glutSolidSphere(2, 10, 10);
		glPopMatrix();
	}
}