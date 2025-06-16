/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: sonarTask.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "sonarTask.h"
#include "GeomUtils.h"
#include "AngleUtils.h"

using namespace std;

//---------------------------------------------------------
// Constructor()

sonarTask::sonarTask()
{
}

//---------------------------------------------------------
// Destructor

sonarTask::~sonarTask()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail()

bool sonarTask::OnNewMail(MOOSMSG_LIST &NewMail)
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

      else if(key == "SONAR_CONF"){
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

bool sonarTask::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool sonarTask::Iterate()
{
  AppCastingMOOSApp::Iterate();
  
    // Initiate points of sonar edge end

    double left_x_1, left_y_1, right_x_1, right_y_1, head_x_1, head_y_1, left_middle_x_1, left_middle_y_1, right_middle_x_1, right_middle_y_1;
    double left_x_2, left_y_2, right_x_2, right_y_2, head_x_2, head_y_2, left_middle_x_2, left_middle_y_2, right_middle_x_2, right_middle_y_2;


    // calculate left and right edge direction by extending points from heading to left and right
    // by half of an angle each direction
    // angle360 function normalize angle to a number from 0-360 deg

    double sonar_1_head_angle = nav_heading + 90;
    double sonar_2_head_angle = nav_heading + 270;

    double left_rad_1 = angle360(sonar_1_head_angle - (angle / 2.0));
    double right_rad_1 = angle360(sonar_1_head_angle + (angle / 2.0));
    double left_middle_rad_1 = angle360(sonar_1_head_angle - (angle / 4.0));
    double right_middle_rad_1 = angle360(sonar_1_head_angle + (angle / 4.0));
    double head_rad_1 = angle360(sonar_1_head_angle);

    double left_rad_2 = angle360(sonar_2_head_angle - (angle / 2.0));
    double right_rad_2 = angle360(sonar_2_head_angle + (angle / 2.0));
    double left_middle_rad_2 = angle360(sonar_2_head_angle - (angle / 4.0));
    double right_middle_rad_2 = angle360(sonar_2_head_angle + (angle / 4.0));
    double head_rad_2 = angle360(sonar_2_head_angle);

    // calculate left and right point of sonar by function projectPoint
    // which calculate left and right point by taking base ship position
    // left and right edge direction and range of sonar

    projectPoint(left_rad_1, range, nav_x, nav_y, left_x_1, left_y_1);
    projectPoint(right_rad_1, range, nav_x, nav_y, right_x_1, right_y_1);
    projectPoint(head_rad_1, range, nav_x, nav_y, head_x_1, head_y_1);
    projectPoint(left_middle_rad_1, range, nav_x, nav_y, left_middle_x_1, left_middle_y_1);
    projectPoint(right_middle_rad_1, range, nav_x, nav_y, right_middle_x_1, right_middle_y_1);

    projectPoint(left_rad_2, range, nav_x, nav_y, left_x_2, left_y_2);
    projectPoint(right_rad_2, range, nav_x, nav_y, right_x_2, right_y_2);
    projectPoint(head_rad_2, range, nav_x, nav_y, head_x_2, head_y_2);
    projectPoint(left_middle_rad_2, range, nav_x, nav_y, left_middle_x_2, left_middle_y_2);
    projectPoint(right_middle_rad_2, range, nav_x, nav_y, right_middle_x_2, right_middle_y_2);


    // add points to polygon
    
    XYPolygon sonar1, sonar2;
    
    sonar1.add_vertex(nav_x, nav_y);
    sonar1.add_vertex(left_x_1, left_y_1);
    sonar1.add_vertex(left_middle_x_1, left_middle_y_1);
    sonar1.add_vertex(head_x_1, head_y_1);
    sonar1.add_vertex(right_middle_x_1, right_middle_y_1);
    sonar1.add_vertex(right_x_1, right_y_1);
    
    sonar2.add_vertex(nav_x, nav_y);
    sonar2.add_vertex(left_x_2, left_y_2);
    sonar2.add_vertex(left_middle_x_2, left_middle_y_2);
    sonar2.add_vertex(head_x_2, head_y_2);
    sonar2.add_vertex(right_middle_x_2, right_middle_y_2);
    sonar2.add_vertex(right_x_2, right_y_2);
    

    sonar1.set_label("SONAR1");
    sonar1.set_color("edge", "red");
    sonar1.set_color("fill", "blue");
    sonar1.set_transparency(0.3);
    sonar1.set_active(true);

    sonar2.set_label("SONAR2");
    sonar2.set_color("edge", "red");
    sonar2.set_color("fill", "blue");
    sonar2.set_transparency(0.3);
    sonar2.set_active(true);

    std::vector<XYPoint> points = { point1, point2, point3 }; 

    double min_distance_sonar_1 = 100000;
    double min_distance_sonar_2 = 100000;


    for (const auto& pt : points) {
      Notify("SONAR_1_DEBUG", std::to_string(sonar1.contains(pt)));

      if (sonar1.contains(pt)) {
        double dx1 = pt.x() - nav_x;
        double dy1 = pt.y() - nav_y;
        double range1 = sqrt(dx1*dx1 + dy1*dy1);
        if (range1 < min_distance_sonar_1) {
          min_distance_sonar_1 = range1;
          double angle_rad = atan2(dx1,dy1);
          double angle_deg = angle_rad * (180.0 / 3.14);
          angle_deg = angle360(angle_deg);
          Notify("SONAR1_INFO", "range=" + std::to_string(range1) + "angle=" + std::to_string(angle_deg));
        }
      } else {
        Notify("SONAR1_INFO", "None");
        min_distance_sonar_1 = 100000;
      }
  
      if (sonar2.contains(pt)) {
        double dx2 = pt.x() - nav_x;
        double dy2 = pt.y() - nav_y;
        double range2 = sqrt(dx2*dx2 + dy2*dy2);
  
        if (range2 < min_distance_sonar_2) {
          min_distance_sonar_2 = range2;
          double angle_rad = atan2(dx2,dy2);
          double angle_deg = angle_rad * (180.0 / 3.14);
          angle_deg = angle360(angle_deg);
          Notify("SONAR2_INFO", "range=" + std::to_string(range2) + "angle=" + std::to_string(angle_deg));
        }
      } else {
        Notify("SONAR2_INFO", "None");
        min_distance_sonar_2 = 100000;
      }
    }

    

    // if (sonar1.contains(point1)) {
    //   double dx1 = point1.x() - nav_x;
    //   double dy1 = point1.y() - nav_y;

    //   double angle_rad = atan2(dx1,dy1);
    //   double angle_deg = angle_rad * (180.0 / 3.14);
    //   angle_deg = angle360(angle_deg);

    //   double range1 = sqrt(dx1*dx1 + dy1*dy1);
    //   Notify("SONAR1_INFO", "range=" + std::to_string(range1) + "angle=" + std::to_string(angle_deg));
    // } else {
    //   Notify("SONAR1_INFO", "None");
    // }

    // if (sonar2.contains(point1)) {
    //   double dx2 = point1.x() - nav_x;
    //   double dy2 = point1.y() - nav_y;

    //   double angle_rad = atan2(dx2,dy2);
    //   double angle_deg = angle_rad * (180.0 / 3.14);
    //   angle_deg = angle360(angle_deg);

    //   double range2 = sqrt(dx2*dx2 + dy2*dy2);
    //   Notify("SONAR2_INFO", "range=" + std::to_string(range2) + "angle=" + std::to_string(angle_deg));
    // } else {
    //   Notify("SONAR2_INFO", "None");
    // }

    // draw polygon
    
    Notify("VIEW_POLYGON",sonar1.get_spec());
    Notify("VIEW_POLYGON",sonar2.get_spec());


  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool sonarTask::OnStartUp()
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

  string str_point1, str_point2, str_point3;

  m_MissionReader.GetValue("point1", str_point1);
  m_MissionReader.GetValue("point2", str_point2);
  m_MissionReader.GetValue("point3", str_point3);

  point1.set_vx(stod(tokStringParse(str_point1, "x", ',', '=')));
  point1.set_vy(stod(tokStringParse(str_point1, "y", ',', '=')));
  point1.set_vertex_size(stod(tokStringParse(str_point1, "vertex_size", ',', '=')));

  point2.set_vx(stod(tokStringParse(str_point2, "x", ',', '=')));
  point2.set_vy(stod(tokStringParse(str_point2, "y", ',', '=')));
  point2.set_vertex_size(stod(tokStringParse(str_point2, "vertex_size", ',', '=')));

  point3.set_vx(stod(tokStringParse(str_point3, "x", ',', '=')));
  point3.set_vy(stod(tokStringParse(str_point3, "y", ',', '=')));
  point3.set_vertex_size(stod(tokStringParse(str_point3, "vertex_size", ',', '=')));
  point_initialized = true;

  Notify("VIEW_POINT", str_point1);
  Notify("VIEW_POINT", str_point2);
  Notify("VIEW_POINT", str_point3);
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables()

void sonarTask::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("SONAR_CONF", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
  Register("NAV_HEADING", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool sonarTask::buildReport() 
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




