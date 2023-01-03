#include "Simulator.h"
#include <stdlib.h>

#include <GL/glut.h>  // (or others, depending on the system in use)
#include "Basic.h"
//	extern Vector3d truckPos;
Simulator::Simulator() {


  for(int i=0; i<1; i++) {
    //pos
    double x = 50+300*(myRand()-0.5);
    double y = 50+300*(myRand()-0.5);
    double z = 0;
    Vector3d pos(-325, 0, 50);
    //vel
    double vx = 20*(myRand()-0.5);
	double vy = 20 * (myRand() - 0.5);
    double vz = 0;
    Vector3d vel(vx,vy,vz);
	double mass = 4 + myRand() * 10; //random between 4 and 14
	double maxVel = 1 + myRand() * 5; //random between 18 and 28
    //double maxAccel = 20+drand48()*10; //random between 20 and 30
	double maxAccel = 20 + myRand() * 10; //random between 20 and 30
	double viewRadius = 40 + myRand() * 10; //random between 40 and 50
//    agents.push_back( Vector3d(x,y) );

   Agent a_i;
   a_i.Init(i,pos,vel,mass,12,maxAccel,viewRadius);
   agents.push_back( a_i );
  }

  for (int i = 0; i<1; i++) {
	  //pos
	  double x = 50 + 300 * (myRand() - 0.5);
	  double y = 50 + 300 * (myRand() - 0.5);
	  double z = 50 + 300 * (myRand() - 0.5);
	  Vector3d pos(x, y, z);
	  //vel
	  double vx = 20 * (myRand() - 0.5);
	  double vy = 20 * (myRand() - 0.5);
	  double vz = 20 * (myRand() - 0.5);
	  Vector3d vel(vx, vy, vz);
	  double mass = 4 + myRand() * 10; //random between 4 and 14
	  double maxVel = 1 + myRand() * 5; //random between 18 and 28
										//double maxAccel = 20+drand48()*10; //random between 20 and 30
	  double maxAccel = 20 + myRand() * 10; //random between 20 and 30
	  double viewRadius = 40 + myRand() * 10; //random between 40 and 50
											  //agents.push_back( Vector3d(x,y) );
	  Agent3D a_j;
	  a_j.Init3D(i, pos, vel, 4, 10, maxAccel, viewRadius);
	  agents3D.push_back(a_j);
  }
}

void Simulator::DrawSimpleMan() {
	for (int i = 0; i<10; i++) {
		//pos
		double x = 50 + 300 * (myRand() - 0.5);
		double y = 50 + 300 * (myRand() - 0.5);
		double z = 0;
		Vector3d pos(x, y, z);
		//vel
		double vx = 20 * (myRand() - 0.5);
		double vy = 20 * (myRand() - 0.5);
		double vz = 0;
		Vector3d vel(vx, vy, vz);
		double mass = 4 + myRand() * 10; //random between 4 and 14
		double maxVel = 1 + myRand() * 5; //random between 18 and 28
										  //double maxAccel = 20+drand48()*10; //random between 20 and 30
		double maxAccel = 20 + myRand() * 10; //random between 20 and 30
		double viewRadius = 40 + myRand() * 10; //random between 40 and 50
												//agents.push_back( Vector3d(x,y) );
		Agent a_i;
		a_i.Init(i, pos, vel, mass, maxVel, maxAccel, viewRadius);
		agents.push_back(a_i);
	}
}

void Simulator::Draw() {
  for(int i=0; i<(int)agents.size(); i++) {
    agents[i].Draw();
  }
}

void Simulator::Update() {
  double dt = 0.25;
  for(int i=0; i<(int)agents.size(); i++) {
    agents[i].Update(agents, dt);
  }
}

void Simulator::Draw3D() {
	for (int i = 0; i<(int)agents3D.size(); i++) {
		agents3D[i].Draw3D();
	}
}

void Simulator::Update3D() {
	double dt = 0.25;
	for (int i = 0; i<(int)agents3D.size(); i++) {
		agents3D[i].Update3D(agents3D, dt);
	}
}