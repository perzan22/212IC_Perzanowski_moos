/************************************************************/
/*    NAME: Olaf Perzanowski                                */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: lab2.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "lab2.h"
#include "GeomUtils.h"

using namespace std;

//---------------------------------------------------------
// Constructor()

lab2::lab2()
{
}

//---------------------------------------------------------
// Destructor

lab2::~lab2()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail()

bool lab2::OnNewMail(MOOSMSG_LIST &NewMail)
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
       else if(key == "CONF_POLYGON"){
        center = tokStringParse(msg.GetString(),"center",',','=');
        width = stod(tokStringParse(msg.GetString(),"width",',','='));
        height = stod(tokStringParse(msg.GetString(),"height",',','='));
        if(center[0] == '('&& center[center.length() -1] == ')'){
        center = center.substr(1,center.length() -2);
        vector<string> v =parseString(center,';');
        rect_x = stod(v[0]);
        rect_y = stod(v[1]);
        }
        //Notify("C",center);
       }

     else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer()

bool lab2::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool lab2::Iterate()
{
  AppCastingMOOSApp::Iterate();
  
  // set x and y of each polygon point depending on center and width of the poly
  XYPoint pkt1,pkt2,pkt3,pkt4;
  pkt1.set_vx(rect_x - width/2);
  pkt1.set_vy(rect_y + height/2);
  
  pkt2.set_vx(rect_x + width/2);
  pkt2.set_vy(rect_y + height/2);
  
  pkt3.set_vx(rect_x + width/2);
  pkt3.set_vy(rect_y - height/2);
  
  pkt4.set_vx(rect_x - width/2);
  pkt4.set_vy(rect_y - height/2);
  
  // add points to polygon
  XYPolygon pol;
  
  pol.add_vertex(pkt1.get_vx(), pkt1.get_vy());
  pol.add_vertex(pkt2.get_vx(), pkt2.get_vy());
  pol.add_vertex(pkt3.get_vx(), pkt3.get_vy());
  pol.add_vertex(pkt4.get_vx(), pkt4.get_vy());
  
  // draw polygon
  Notify("VIEW_POLYGON",pol.get_spec());
  
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool lab2::OnStartUp()
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

void lab2::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("CONF_POLYGON", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool lab2::buildReport() 
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




