/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: komunikatorSNR.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef komunikatorSNR_HEADER
#define komunikatorSNR_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class komunikatorSNR : public AppCastingMOOSApp
{
 public:
   komunikatorSNR();
   ~komunikatorSNR();

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
