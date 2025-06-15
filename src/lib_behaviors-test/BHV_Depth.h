/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_Depth.h                                      */
/*    DATE:                                                 */
/************************************************************/

#ifndef Depth_HEADER
#define Depth_HEADER

#include <string>
#include "IvPBehavior.h"

class BHV_Depth : public IvPBehavior {
public:
  BHV_Depth(IvPDomain);
  ~BHV_Depth() {};
  
  bool         setParam(std::string, std::string);
  void         onSetParamComplete();
  void         onCompleteState();
  void         onIdleState();
  void         onHelmStart();
  void         postConfigStatus();
  void         onRunToIdleState();
  void         onIdleToRunState();
  IvPFunction* onRunState();

protected: // Local Utility functions

  bool updateInfoIn();

protected: // Configuration parameters
  double m_desired_depth;
  double m_depth;
  double m_water_depth;
  double m_max_depth;

protected: // State variables
};

#define IVP_EXPORT_FUNCTION

extern "C" {
  IVP_EXPORT_FUNCTION IvPBehavior * createBehavior(std::string name, IvPDomain domain) 
  {return new BHV_Depth(domain);}
}
#endif
