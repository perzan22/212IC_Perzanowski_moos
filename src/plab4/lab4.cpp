/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: lab4.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "lab4.h"
#include "GeomUtils.h"

using namespace std;

//---------------------------------------------------------
// Constructor()

lab4::lab4()
{
  // initial timer values set to 0
  isInside = false;
  entryTime = 0.0;
  timeInPolygon = 0.0;
  totalTimeInPolygon = 0.0;
}

//---------------------------------------------------------
// Destructor

lab4::~lab4()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail()

bool lab4::OnNewMail(MOOSMSG_LIST &NewMail)
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

       // get polygon posuition from komunikator
       else if(key == "CONF_POLYGON"){
        center = tokStringParse(msg.GetString(),"center",',','=');
        width = stod(tokStringParse(msg.GetString(),"width",',','='));
        if(center[0] == '('&& center[center.length() -1] == ')'){
          center = center.substr(1,center.length() -2);
          vector<string> v =parseString(center,';');
          rect_x = stod(v[0]);
          rect_y = stod(v[1]);
        }
        //Notify("C",center);
       }
       // get kayak actual position
       else if(key == "NAV_X"){
        nav_x = msg.GetDouble();
       }
       else if(key == "NAV_Y"){
        nav_y = msg.GetDouble();
       }

     else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer()

bool lab4::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool lab4::Iterate()
{
  AppCastingMOOSApp::Iterate();

  // add points of polygon

  XYPoint pkt1, pkt2, pkt3, pkt4;

  pkt1.set_vx(rect_x - width/2);
  pkt1.set_vy(rect_y + width/2);
  
  pkt2.set_vx(rect_x + width/2);
  pkt2.set_vy(rect_y + width/2);
  
  pkt3.set_vx(rect_x + width/2);
  pkt3.set_vy(rect_y - width/2);
  
  pkt4.set_vx(rect_x - width/2);
  pkt4.set_vy(rect_y - width/2);
  
  // draw polygon

  XYPolygon pol;
  
  pol.add_vertex(pkt1.get_vx(), pkt1.get_vy());
  pol.add_vertex(pkt2.get_vx(), pkt2.get_vy());
  pol.add_vertex(pkt3.get_vx(), pkt3.get_vy());
  pol.add_vertex(pkt4.get_vx(), pkt4.get_vy());

  pol.set_label("POLYGON"); 
  pol.set_active(true);

  // get actual time

  double current_time = MOOSTime();

  // set polygon color if kayak is inside and let timer work

  if (pol.contains(nav_x, nav_y)) {
    pol.set_color("edge", "green");
    pol.set_color("fill", "blue");
    pol.set_transparency(0.3);

    // if kayak just entered polygon set entry time
    if (!isInside) {
      entryTime = current_time;
      isInside = true;
    }

    // count time spent in polygon
    timeInPolygon = current_time - entryTime;
  } else {
    // if kayak just left the polygon stop, reset timer and add current timer value to total time
    if (isInside) {
      totalTimeInPolygon += current_time - entryTime;
      isInside = false;
      timeInPolygon = 0.0;
    }
  }

  // total time to print is the total previous time of kayak in polygon
  // + time of possible current time in polygon
  double totalTime = totalTimeInPolygon;
  if (isInside) {
    totalTime += timeInPolygon;
  }
  
  // store polygon variable and time in polygon
  Notify("VIEW_POLYGON",pol.get_spec());
  Notify("TIME_IN_POLYGON", totalTime);

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool lab4::OnStartUp()
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
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables()

void lab4::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("CONF_POLYGON", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool lab4::buildReport() 
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




