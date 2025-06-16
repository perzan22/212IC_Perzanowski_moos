/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: sonarTask.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef sonarTask_HEADER
#define sonarTask_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "GeomUtils.h"
#include "XYPoint.h"
#include "XYPolygon.h"
using namespace std;


class sonarTask : public AppCastingMOOSApp
{
 public:
   sonarTask();
   ~sonarTask();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

 private: // Configuration variables
  double range;
  double angle;

  // actual kayak positions variables
  double nav_x;
  double nav_y;
  double nav_heading;

  XYPoint point1;
  XYPoint point2;
  XYPoint point3;
  bool point_initialized = false;

  // difference between sonar and point
  double dx;
  double dy;


 private: // State variables
};

#endif 
