/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_Depth.cpp                                    */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include <cstdlib>
#include "MBUtils.h"
#include "BuildUtils.h"
#include "BHV_Depth.h"
#include "ZAIC_PEAK.h"

using namespace std;

//---------------------------------------------------------------
// Constructor

BHV_Depth::BHV_Depth(IvPDomain domain) :
  IvPBehavior(domain)
{
  // Provide a default behavior name
  IvPBehavior::setParam("name", "depth_survey");

  // Declare the behavior decision space
  m_domain = subDomain(m_domain, "depth");

  // Add any variables this behavior needs to subscribe for
  addInfoVars("NAV_DEPTH");
  m_desired_depth = 0;
  m_depth = 0;
  m_water_depth = 0;
  m_max_depth = 0;
}

//---------------------------------------------------------------
// Procedure: setParam()

bool BHV_Depth::setParam(string param, string val)
{
  // Convert the parameter to lower case for more general matching
  param = tolower(param);

  // Get the numerical value of the param argument for convenience once
  double double_val = atof(val.c_str());
  
  if((param == "d_depth") && isNumber(val)) {
    // Set local member variables here
    m_desired_depth = double_val;
    return(true);
  }

  if((param == "w_depth") && isNumber(val)) {
    // Set local member variables here
    m_water_depth = double_val;
    return(true);
  }

  if((param == "max_depth") && isNumber(val)) {
    // Set local member variables here
    m_max_depth = double_val;
    return(true);
  }
  // If not handled above, then just return false;
  return(false);
}

//---------------------------------------------------------------
// Procedure: onSetParamComplete()
//   Purpose: Invoked once after all parameters have been handled.
//            Good place to ensure all required params have are set.
//            Or any inter-param relationships like a<b.

void BHV_Depth::onSetParamComplete()
{
}

//---------------------------------------------------------------
// Procedure: onHelmStart()
//   Purpose: Invoked once upon helm start, even if this behavior
//            is a template and not spawned at startup

void BHV_Depth::onHelmStart()
{
}

//---------------------------------------------------------------
// Procedure: onIdleState()
//   Purpose: Invoked on each helm iteration if conditions not met.

void BHV_Depth::onIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onCompleteState()

void BHV_Depth::onCompleteState()
{
}

//---------------------------------------------------------------
// Procedure: postConfigStatus()
//   Purpose: Invoked each time a param is dynamically changed

void BHV_Depth::postConfigStatus()
{
}

//---------------------------------------------------------------
// Procedure: onIdleToRunState()
//   Purpose: Invoked once upon each transition from idle to run state

void BHV_Depth::onIdleToRunState()
{
}

//---------------------------------------------------------------
// Procedure: onRunToIdleState()
//   Purpose: Invoked once upon each transition from run to idle state

void BHV_Depth::onRunToIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onRunState()
//   Purpose: Invoked each iteration when run conditions have been met.

IvPFunction* BHV_Depth::onRunState()
{

  updateInfoIn();
  if (!m_domain.hasDomain("depth")) {
    postEMessage("No depth variable in the helm domain");
    return 0;
  }


  // Part 1: Build the IvP function
  ZAIC_PEAK zaic(m_domain, "depth");

  
  if ((m_water_depth - m_desired_depth) < m_max_depth) {
    zaic.setSummit(m_water_depth - m_desired_depth);
  } else {
    zaic.setSummit(m_max_depth);
  }
  zaic.setBaseWidth(100);
  zaic.setPeakWidth(3);
  zaic.setSummitDelta(50);

  IvPFunction *ipf = zaic.extractIvPFunction();



  // Part N: Prior to returning the IvP function, apply the priority wt
  // Actual weight applied may be some value different than the configured
  // m_priority_wt, depending on the behavior author's insite.
  if(ipf)
    ipf->setPWT(m_priority_wt);
  else {
    postEMessage("Unable to generate depth holder IvP function");
  }

  string zaic_warnings = zaic.getWarnings();
  if (zaic_warnings != "") {
    postWMessage(zaic_warnings);
  }

  return(ipf);
}

bool BHV_Depth::updateInfoIn()
{
  bool ok;

  m_depth = getBufferDoubleVal("NAV_DEPTH", ok);

  if (!ok) {
    postWMessage("No ownship DEPTH info in info_buffer.");
    return(false);
  }

  return (true);
}