/************************************************************/
/*    NAME: Olaf Perzanowski                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: lab2_1.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include <cmath>
#include "MBUtils.h"
#include "ACTable.h"
#include "lab2_1.h"
#include "GeomUtils.h"

using namespace std;

//---------------------------------------------------------
// Constructor()

lab2_1::lab2_1()
{
}

//---------------------------------------------------------
// Destructor

lab2_1::~lab2_1()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail()

bool lab2_1::OnNewMail(MOOSMSG_LIST &NewMail)
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

bool lab2_1::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool lab2_1::Iterate()
{
  AppCastingMOOSApp::Iterate();
  
  XYPolygon pol;
  
  for (int i = 0; i < 8; i++) {
    // set angle
    double angle = i * M_PI / 4.0;

    // set x variable
    double x = rect_x + (width / 2.0) * cos(angle);
    // set y variable
    double y = rect_y + (width / 2.0) * sin(angle);

    // add point to polygon
    pol.add_vertex(x, y);
  }
  
  Notify("VIEW_POLYGON",pol.get_spec());
  
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool lab2_1::OnStartUp()
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

void lab2_1::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("CONF_POLYGON", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool lab2_1::buildReport() 
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




