/************************************************************/
/*    NAME: Tyler Paine                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: OpinionFixer.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "OpinionFixer.h"

using namespace std;

//---------------------------------------------------------
// Constructor()

OpinionFixer::OpinionFixer()
{
}

//---------------------------------------------------------
// Destructor

OpinionFixer::~OpinionFixer()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail()

bool OpinionFixer::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    string sval  = msg.GetString(); 

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
   
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

    if(key == m_input_var){
      if ( (sval == "explore") || (sval == "exploit")) {
	// fix these options based on the configuration
	if (m_explore_set.count(m_vname) > 0) {
	  Notify(m_output_var, "explore"); 
	} else if (m_exploit_set.count(m_vname) > 0) {
	  Notify(m_output_var, "exploit"); 
	} else {
	  // just pass it through
	  Notify(m_output_var, sval);
	}

      } else {
	// just pass it through
	Notify(m_output_var, sval); 
      }

    }
    else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer()

bool OpinionFixer::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool OpinionFixer::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool OpinionFixer::OnStartUp()
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
    if(param == "input_var_name") {
      m_input_var = value;
      handled = true;
    }
    else if(param == "output_var_name") {
      m_output_var = value;
      handled = true;
    }
    else if(param == "persistent_exploit_set") {
      handled = true;

      vector<string> msgs = parseString(value, ',');
      for(unsigned int i=0; i<msgs.size(); i++) {
	string msg = stripBlankEnds(msgs[i]);
	// Check if proper NMEA Header
	if(msg != "")
	  m_exploit_set.insert(msg);
	else
	  handled = false;
      }

    }
     else if(param == "persistent_explore_set") {
      handled = true;

      vector<string> msgs = parseString(value, ',');
      for(unsigned int i=0; i<msgs.size(); i++) {
	string msg = stripBlankEnds(msgs[i]);
	// Check if proper NMEA Header
	if(msg != "")
	  m_explore_set.insert(msg);
	else
	  handled = false;
      }

    }
    
    if(!handled)
      reportUnhandledConfigWarning(orig);

  }

  bool vnameOk = m_MissionReader.GetValue("Community", m_vname);
  if (!vnameOk) {
    reportUnhandledConfigWarning("Not able to get vehicle name");
  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables()

void OpinionFixer::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register(m_input_var, 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool OpinionFixer::buildReport() 
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



