/************************************************************/
/*    NAME:  Olaf Perzanowski                                             */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: lab5.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef lab5_HEADER
#define lab5_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "GeomUtils.h"
#include "XYPoint.h"
#include "XYPolygon.h"
using namespace std;

class lab5 : public AppCastingMOOSApp
{
 public:
   lab5();
   ~lab5();

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



 private: // State variables
};

#endif 
