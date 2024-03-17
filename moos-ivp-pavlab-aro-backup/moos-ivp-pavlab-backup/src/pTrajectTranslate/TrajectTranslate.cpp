/************************************************************/
/*    NAME: Tyler Paine                                     */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: TrajectTranslate.cpp                            */
/*    DATE: March 14th, 2023                                */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "TrajectTranslate.h"

using namespace std;

//---------------------------------------------------------
// Constructor()

TrajectTranslate::TrajectTranslate()
{

  // Config
  m_body_heading_var     = "COMPASS_HEADING_RAW";
  m_time_window          = 0.5;
  
  m_time_const_vel_x = 1.0 / 20.0;
  m_time_const_vel_y = 1.0 / 20.0;
  m_time_const_ang_z = 1.0 / 20.0;
  
  m_heading_rate_scale = 0.1; 

  // State
  m_desired_heading     = -1;
  m_desired_speed       = -1;
  m_compass_heading_raw = -1;
  
  m_desired_heading_time = 0;
  m_desired_speed_time   = 0;
  m_compass_heading_raw_time  = 0;

  m_des_traject_vel_x_last = 0;
  m_des_traject_vel_y_last = 0;
  m_des_traject_ang_z_last = 0;

  m_last_publish_time = 0;

  m_got_desired_heading        = false;
  m_got_desired_speed          = false;
  m_got_compass_heading_raw    = false;
  m_deploy                     = false;
  m_des_speed_in_surge_only    = false; 
  
  
}

//---------------------------------------------------------
// Destructor

TrajectTranslate::~TrajectTranslate()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail()

bool TrajectTranslate::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    double dval  = msg.GetDouble();
    

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

    if(key == "DESIRED_SPEED") {
      m_desired_speed = dval;
      m_desired_speed_time = MOOSTime();
      m_got_desired_speed = true; 
    } else if (key == "DESIRED_HEADING") {
      m_desired_heading = dval;
      m_desired_heading_time = MOOSTime();
      m_got_desired_heading = true;
    } else if (key == m_body_heading_var) {
      m_compass_heading_raw = dval;
      m_compass_heading_raw_time = MOOSTime();
      m_got_compass_heading_raw = true;
    } else if (key == "DEPLOY") {
      bool ok1 = setBooleanOnString(m_deploy, msg.GetString());
    } else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer()

bool TrajectTranslate::OnConnectToServer()
{
  //registerVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool TrajectTranslate::Iterate()
{
  AppCastingMOOSApp::Iterate();

  // Bail if not ready
  if (!checkReadyToGo()) {
     AppCastingMOOSApp::PostReport();
     return(true);
  }

  // Step 1.  Translate the current helm decision
  //          into body coordinates: surge, sway
  //          and yaw rate.
  //          This can be configured such that all
  //          of the desired speed is always in the
  //          surge degree of freedom.
  //          See des_speed_in_surge_only param 


  // Step 1.1   Calculate the delta theta
  double deg_to_rad = M_PI/180.0;
  double rad_to_deg = 180.0/M_PI;
  
  // Unit vectors
  double a1 = sin(deg_to_rad*m_compass_heading_raw); 
  double a2= cos(deg_to_rad*m_compass_heading_raw);  
  
  double b1 = sin(deg_to_rad*m_desired_heading);     
  double b2 = cos(deg_to_rad*m_desired_heading);     

  double k = a1*b2 - a2*b1;  // a cross b
  double dot_a_b = a1*b1+ a2*b2;

  double delta_theta;
  if (k >=0){
    delta_theta = rad_to_deg * acos(dot_a_b) * (-1.0);
  } else {
    delta_theta = rad_to_deg * acos(dot_a_b) * (1.0);
  }

  
  // Step 1.2  Calculate the des velocity in x and y.
  //           depending on the configuration.
  double des_traject_vel_x;
  double des_traject_vel_y;
  if (m_des_speed_in_surge_only){
    des_traject_vel_x = m_desired_speed;
    des_traject_vel_y = 0.0; 
  } else {
    des_traject_vel_x = m_desired_speed * cos( delta_theta * M_PI / 180.0 );
    des_traject_vel_y = m_desired_speed * sin( delta_theta * M_PI / 180.0 );
  }
  
  double des_traject_ang_z = m_heading_rate_scale * delta_theta;
  

  // Step 2.  Compute the filtered values and publish
  // All of the above
  double delta_t = MOOSTime() - m_last_publish_time;
  double alpha;
  
  // Vel_x
  alpha = 1.0 - exp( -1.0 * delta_t / m_time_const_vel_x);
  m_des_traject_vel_x_last +=  alpha * (des_traject_vel_x - m_des_traject_vel_x_last);

  // Vel_y
  alpha = 1.0 - exp( -1.0 * delta_t / m_time_const_vel_y);
  m_des_traject_vel_y_last +=  alpha * (des_traject_vel_y - m_des_traject_vel_y_last);

  // Ang_z
  alpha = 1.0 - exp( -1.0 * delta_t / m_time_const_ang_z);
  m_des_traject_ang_z_last +=  alpha * (des_traject_ang_z - m_des_traject_ang_z_last);
  


  Notify("DESIRED_VEL_TWIST_LINEAR_X", m_des_traject_vel_x_last);
  Notify("DESIRED_VEL_TWIST_LINEAR_Y", m_des_traject_vel_y_last);
  Notify("DESIRED_VEL_TWIST_ANGULAR_Z", m_des_traject_ang_z_last*deg_to_rad);


  std::string udes_string = std::to_string(m_des_traject_vel_x_last);
  std::string udes_header = "u(";
  std::string vdes_string = std::to_string(m_des_traject_vel_y_last);
  std::string vdes_header = ")v(";
  std::string rdes_string = std::to_string(m_des_traject_ang_z_last*deg_to_rad);
  std::string rdes_header = ")r(";
  std::string end_char = ")";
  std::string m_des_full_state = udes_header + udes_string + vdes_header + vdes_string + rdes_header + rdes_string + end_char;

  Notify("DESIRED_FULL_STATE", m_des_full_state);

  m_last_publish_time = MOOSTime();
  
  
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool TrajectTranslate::OnStartUp()
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
    if(param == "time_window") {
      handled = setPosDoubleOnString(m_time_window, value);
    }
    else if(param == "heading_rate_scale") {
      handled = setPosDoubleOnString(m_heading_rate_scale,value);
    }
    else if(param == "body_heading_var") {
      if(!strContainsWhite(value)) {m_body_heading_var=toupper(value); handled=true;}

    }
    else if(param == "cutoff_freq_vel_x") {
      double cutoff;
      bool ok = setPosDoubleOnString(cutoff,value);
      m_time_const_vel_x = 1.0 / cutoff;  // Cutoff cannot be zero.
      handled = ok;
    }
    else if(param == "cutoff_freq_vel_y") {
      double cutoff;
      bool ok = setPosDoubleOnString(cutoff,value);
      m_time_const_vel_y = 1.0 / cutoff;  // Cutoff cannot be zero.
      handled = ok;
    }
    else if(param == "cutoff_freq_ang_z") {
      double cutoff;
      bool ok = setPosDoubleOnString(cutoff,value);
      m_time_const_ang_z = 1.0 / cutoff;  // Cutoff cannot be zero.
      handled = ok;
    }
    else if(param == "des_speed_in_surge_only") {
      handled = setBooleanOnString(m_des_speed_in_surge_only, value);
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  
  registerVariables();

  // initialize times
  m_desired_heading_time = MOOSTime();
  m_desired_speed_time   = MOOSTime();
  m_compass_heading_raw_time  = MOOSTime();
  m_last_publish_time = MOOSTime();
  
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables()

void TrajectTranslate::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("DESIRED_HEADING", 0);
  Register("DESIRED_SPEED", 0);
  Register("DEPLOY",0);
  Register(m_body_heading_var,0);
  
}


//------------------------------------------------------------
// Procedure: buildReport()

bool TrajectTranslate::buildReport() 
{
  if (checkReadyToGo())
    m_msgs << " Trajectory Translation Running:            " << endl;
  else {
    m_msgs << " **Trajectory Translation Timed Out**       " << endl;
    
    double dt_hdg = abs(m_desired_heading_time - MOOSTime());
    if (dt_hdg > m_time_window)
      m_msgs << " ** Late DESIRED_HEADING msg, " << doubleToStringX(dt_hdg,3) << "s since last. " << endl;
    
    double dt_spd = abs(m_desired_speed_time - MOOSTime());
    if (dt_spd > m_time_window)
      m_msgs << " ** Late DESIRED_SPEED msg, " << doubleToStringX(dt_spd,3) << "s since last. " << endl;
    
    double dt_comp = abs(m_compass_heading_raw_time - MOOSTime());
    if (dt_comp > m_time_window)
      m_msgs << " ** Late COMPASS_HEADING_RAW msg, " << doubleToStringX(dt_comp,3) << "s since last. " << endl;
  }
  m_msgs << "                                            " << endl;
  m_msgs << "First-Order Filter Time Constants:          " << endl;
  m_msgs << "============================================" << endl; 

  string tau_x_str   = doubleToString(m_time_const_vel_x,2);
  string tau_y_str   = doubleToString(m_time_const_vel_y,2);
  string tau_yaw_str = doubleToString(m_time_const_ang_z,2);

  ACTable actab1(3);
  actab1 << "Vel X | Vel Y | Yaw Rate";
  actab1.addHeaderLines();
  actab1 << tau_x_str << tau_y_str << tau_yaw_str ;
  m_msgs << actab1.getFormattedString();

  m_msgs << "                                            " << endl;
  m_msgs << "                                            " << endl;
  m_msgs << "Filter States:                              " << endl;
  m_msgs << "============================================" << endl;
  
  ACTable actab2(4);
  actab2 << " | Speed (m/s) | Heading (deg) | Current Compass (deg)";
  actab2.addHeaderLines();
  actab2 << "Last Helm Decision:" << doubleToString(m_desired_speed,2)
	<< doubleToString(m_desired_heading,2) << doubleToString(m_compass_heading_raw,2) ;
  m_msgs << actab2.getFormattedString();
  
  m_msgs << "                                            " << endl;
  m_msgs << "============================================" << endl;
  ACTable actab3(4);
  actab3 << " | Vel X (Surge m/s) | Vel Y (Sway m/s) | Ang Z (Yaw Rate deg/sec)";
  actab3.addHeaderLines();
  actab3 << "Last Output:" << doubleToString(m_des_traject_vel_x_last,2)
	<< doubleToString(m_des_traject_vel_y_last,2) << doubleToString(m_des_traject_ang_z_last,2) ;
  m_msgs << actab3.getFormattedString();
  m_msgs << "                                            " << endl;

  m_msgs << "Time since last output: " << doubleToString(MOOSTime() - m_last_publish_time)
	 << "s" << endl;


  return(true);
}




//------------------------------------------------------------
// Procedure: checkReadyToGo()
//            General check of readiness
//            Returns true if all messages were recieved within
//            the time window,

bool TrajectTranslate::checkReadyToGo()
{

  if (!m_deploy)
    return(false);
  
  // Check we have recieved at least one messgae
  if (!m_got_desired_heading || !m_got_desired_speed || !m_got_compass_heading_raw)
    return(false);

  // check staleness 
  if ((MOOSTime() - m_desired_heading_time) > m_time_window)
    return(false);
  if ((MOOSTime() - m_desired_speed_time) > m_time_window)
    return(false);
  if ((MOOSTime() - m_compass_heading_raw_time) > m_time_window)
    return(false);

  return(true);
}