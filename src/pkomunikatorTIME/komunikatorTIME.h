/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: komunikatorTIME.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef komunikatorTIME_HEADER
#define komunikatorTIME_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class komunikatorTIME : public AppCastingMOOSApp
{
 public:
   komunikatorTIME();
   ~komunikatorTIME();

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

 private: // State variables
};

#endif 
