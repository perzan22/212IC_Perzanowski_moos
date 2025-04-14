/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: lab2_1.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef lab2_1_HEADER
#define lab2_1_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "GeomUtils.h"
#include "XYPoint.h"
#include "XYPolygon.h"
using namespace std;

class lab2_1 : public AppCastingMOOSApp
{
 public:
   lab2_1();
   ~lab2_1();

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

 private: // State variables
};

#endif 
