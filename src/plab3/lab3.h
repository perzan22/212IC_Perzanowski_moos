/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: lab3.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef lab3_HEADER
#define lab3_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "GeomUtils.h"
#include "XYPoint.h"
#include "XYPolygon.h"
using namespace std;

class lab3 : public AppCastingMOOSApp
{
 public:
   lab3();
   ~lab3();

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
  double nav_x;
  double nav_y;
  double nav_heading;

 private: // State variables
};

#endif 
