/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: lab4.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef lab4_HEADER
#define lab4_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "GeomUtils.h"
#include "XYPoint.h"
#include "XYPolygon.h"
using namespace std;

class lab4 : public AppCastingMOOSApp
{
 public:
   lab4();
   ~lab4();

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
  string center;
  double width;
  double rect_x;
  double rect_y;
  XYPoint pkt;
  // kayak position variables
  double nav_x;
  double nav_y;

  // timer variables
  bool isInside;
  double entryTime;
  double timeInPolygon;
  double totalTimeInPolygon;

 private: // State variables
};

#endif 
