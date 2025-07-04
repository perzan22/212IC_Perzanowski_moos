/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: lab6.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "lab6.h"
#include "GeomUtils.h"
#include "AngleUtils.h"

using namespace std;

//---------------------------------------------------------
// Constructor()

lab6::lab6()
{
}

//---------------------------------------------------------
// Destructor

lab6::~lab6()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail()

bool lab6::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

      if(key == "FOO") 
      cout << "great!";
      // get sonar info
      else if(key == "SONAR_INFO"){
        range = stod(tokStringParse(msg.GetString(),"range",',','='));
        angle = stod(tokStringParse(msg.GetString(),"angle",',','='));
      }
      // get actual kayak position and heading info
      else if(key == "NAV_X"){
        nav_x = msg.GetDouble();
      }
      else if(key == "NAV_Y"){
        nav_y = msg.GetDouble();
      }
      else if(key == "NAV_HEADING"){
        nav_heading = msg.GetDouble();
      }

      else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer()

bool lab6::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool lab6::Iterate()
{
  AppCastingMOOSApp::Iterate();
  
  // Initiate points of sonar edge end

  double left_x, left_y, right_x, right_y, head_x, head_y, left_middle_x, left_middle_y, right_middle_x, right_middle_y;

  // calculate left and right edge direction by extending points from heading to left and right
  // by half of an angle each direction
  // angle360 function normalize angle to a number from 0-360 deg

  double left_rad = angle360(nav_heading - (angle / 2.0));
  double right_rad = angle360(nav_heading + (angle / 2.0));
  double left_middle_rad = angle360(nav_heading - (angle / 4.0));
  double right_middle_rad = angle360(nav_heading + (angle / 4.0));
  double head_rad = angle360(nav_heading);

  // calculate left and right point of sonar by function projectPoint
  // which calculate left and right point by taking base ship position
  // left and right edge direction and range of sonar

  projectPoint(left_rad, range, nav_x, nav_y, left_x, left_y);
  projectPoint(right_rad, range, nav_x, nav_y, right_x, right_y);
  projectPoint(head_rad, range, nav_x, nav_y, head_x, head_y);
  projectPoint(left_middle_rad, range, nav_x, nav_y, left_middle_x, left_middle_y);
  projectPoint(right_middle_rad, range, nav_x, nav_y, right_middle_x, right_middle_y);

  // add points to polygon
  
  XYPolygon pol;
  
  pol.add_vertex(nav_x, nav_y);
  pol.add_vertex(left_x, left_y);
  pol.add_vertex(left_middle_x, left_middle_y);
  pol.add_vertex(head_x, head_y);
  pol.add_vertex(right_middle_x, right_middle_y);
  pol.add_vertex(right_x, right_y);
  

  pol.set_label("SONAR");
  pol.set_color("edge", "red");
  pol.set_color("fill", "blue");
  pol.set_transparency(0.3);
  pol.set_active(true);

  int object_count = 0;

  if (pol.contains(point1) && point_initialized) {
      object_count++;
      Notify("RETURN", "true");

      dx = point1.x() - nav_x;
      dy = point1.y() - nav_y;

      isAttached = true;
  }

  if (isAttached) {

    point1.set_vx(nav_x + dx);
    point1.set_vy(nav_y + dy);
    point1.set_label("point1");
    point1.set_vertex_size(4);

    Notify("VIEW_POINT", point1.get_spec());
  }

  std::string count_msg = "object_count=" + std::to_string(object_count);

  // draw polygon
  
  Notify("VIEW_POLYGON",pol.get_spec());
  Notify("SNR_INFO", count_msg);

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool lab6::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = tolower(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "foo") {
      handled = true;
    }
    else if(param == "bar") {
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }

  string str_point1;

  m_MissionReader.GetValue("point1", str_point1);

  point1.set_vx(stod(tokStringParse(str_point1, "x", ',', '=')));
  point1.set_vy(stod(tokStringParse(str_point1, "y", ',', '=')));
  point1.set_vertex_size(stod(tokStringParse(str_point1, "vertex_size", ',', '=')));
  point_initialized = true;

  Notify("VIEW_POINT", str_point1);

  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables()

void lab6::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("SONAR_CONF", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
  Register("NAV_HEADING", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool lab6::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "File:                                       " << endl;
  m_msgs << "============================================" << endl;

  ACTable actab(4);
  actab << "Alpha | Bravo | Charlie | Delta";
  actab.addHeaderLines();
  actab << "one" << "two" << "three" << "four";
  m_msgs << actab.getFormattedString();

  return(true);
}




