#ifndef SIMULATOR
#define SIMULATOR

#include "Vector.h"
using namespace mathtool;

#include "Agent.h"
#include "Agent3D.h"

#include <vector>
using namespace std;

class Simulator {
   public:
      Simulator(); 

      void Draw();
      void Update();
	  void DrawSimpleMan();

	  void Draw3D();
	  void Update3D();
   private:
      vector<Agent> agents;
	  vector<Agent3D> agents3D;
};

#endif
