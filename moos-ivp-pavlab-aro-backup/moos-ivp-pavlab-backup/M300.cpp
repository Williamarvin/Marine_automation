/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: M300.cpp                                             */
/*    DATE: 01 APRIL 2020                                        */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include "MBUtils.h"
#include "LatLonFormatUtils.h"
#include "M300.h"
#include "c_library_v2/common/mavlink.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int pik_port = -1;

std::string  m_nav_prefix;
std::string  m_gps_prefix;
std::string  m_compass_prefix;

void M300::fakeGPS(){
  string lat = "100";
  string lon = "2";
  string hdg = "189";
  string speed = "20";

  Notify(m_nav_prefix+"_LAT", lat, "GPRMC");
  Notify(m_nav_prefix+"_LON", lon, "GPRMC");
  Notify(m_nav_prefix+"_LONG", lon, "GPRMC");
  Notify(m_gps_prefix+"_LAT", lat, "GPRMC");
  Notify(m_gps_prefix+"_LON", lon, "GPRMC");
  Notify(m_gps_prefix+"_LONG", lon, "GPRMC");      
  Notify(m_nav_prefix+"_X", lat, "GPRMC");
  Notify(m_nav_prefix+"_Y", lon, "GPRMC");
  Notify(m_gps_prefix+"_X", lat, "GPRMC");
  Notify(m_gps_prefix+"_Y", lon, "GPRMC");    
  Notify(m_nav_prefix+"_SPEED", speed, "GPRMC");      
  Notify(m_nav_prefix+"_HEADING", hdg, "GPRMC");
  Notify("GPS_HEADING", hdg, "GPRMC");

  m_nav_hdg = stod(hdg);
  m_nav_spd = stod(speed);
  m_nav_x = stod(lat);
  m_nav_y = stod(lon);
}

void M300::sendServo(uint8_t servoNumber, float pwmValue)
{
    mavlink_message_t msg;
    int inputValue = pwmValue;
    if (inputValue >= 0) {
        // Map the range [0, 100] to [1500, 2000]
        inputValue = std::max(0, std::min(inputValue, 100));
        float coefficient = static_cast<float>(inputValue) / 100;
        mappedValue = 1500 + (coefficient * 500);
    } else {
        // Map the range [-100, 0] to [1000, 1500]
        inputValue = std::max(-100, std::min(inputValue, 0));
        float coefficient = static_cast<float>(inputValue + 100) / 100;
        mappedValue = 1000 + (coefficient * 500);
    }
    pwmValue = mappedValue;
    //servo 3. left
    mavlink_msg_command_long_pack( 
        1,
        0,
        &msg,
        0,
        0,
        MAV_CMD_DO_SET_SERVO, 
        0,
        servoNumber,
        pwmValue,0,0,0,0,0
    );
 //   sleep(10);
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    cout << pwmValue << endl;
    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
   
    ssize_t bytesWritten = write(pik_port, buffer, len);
}

void M300::receiveComm(){
    const int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];

    ssize_t num_bytes = read(pik_port, buffer, BUFFER_SIZE);
        // cout << buffer;

      for (int i = 0; i < num_bytes; ++i) {
          mavlink_message_t msg;
          mavlink_status_t status;

          if (mavlink_parse_char(MAVLINK_COMM_0, buffer[i], &msg, &status)) {
              // Message parsed successfully
//              printf("Received message with ID %d, sequence: %d from component %d of system %d\n", msg.msgid, msg.seq, msg.compid, msg.sysid);
              switch (msg.msgid) {
                  // Handle specific message types
                  case MAVLINK_MSG_ID_HEARTBEAT:
                  {
                      mavlink_heartbeat_t heartbeat;
                      mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                      // Process heartbeat message
                      break;
                  }
                  
                  case MAVLINK_MSG_ID_GPS_RAW_INT:
                  {
                    mavlink_gps_raw_int_t packet;
                    mavlink_msg_gps_raw_int_decode(&msg, &packet);
//                    cout << "hello" << endl;
                    Notify(m_nav_prefix+"_LAT", to_string(packet.lat), "GPRMC");
                    Notify(m_nav_prefix+"_LON", to_string(packet.lon), "GPRMC");
                    Notify(m_nav_prefix+"_LONG", to_string(packet.lon), "GPRMC");
                    Notify(m_gps_prefix+"_LAT", to_string(packet.lat), "GPRMC");
                    Notify(m_gps_prefix+"_LON", to_string(packet.lon), "GPRMC");
                    Notify(m_gps_prefix+"_LONG", to_string(packet.lon), "GPRMC");      
                    Notify(m_nav_prefix+"_X", to_string(packet.lat), "GPRMC");
                    Notify(m_nav_prefix+"_Y", to_string(packet.lon), "GPRMC");
                    Notify(m_gps_prefix+"_X", to_string(packet.lat), "GPRMC");
                    Notify(m_gps_prefix+"_Y", to_string(packet.lon), "GPRMC");    
                    Notify(m_nav_prefix+"_SPEED", to_string(packet.vel), "GPRMC");      
                    Notify(m_nav_prefix+"_HEADING", to_string(packet.yaw), "GPRMC");
                    Notify("GPS_HEADING", to_string(packet.yaw), "GPRMC");

                    cout <<"GPS Latitude: "; cout << packet.lat;
                    cout <<"GPS Longitude: "; cout << packet.lon;
                    cout <<"GPS Speed: "; cout << packet.vel;
                    // cout <<"Sats Visible: "; cout << packet.satellites_visible;
  		    m_nav_hdg = packet.yaw;
                    m_nav_spd = packet.vel;
                    m_nav_x = packet.lat;
                    m_nav_y = packet.lon;      
 }

                  case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
                  {
                      mavlink_servo_output_raw_t packet;
                      mavlink_msg_servo_output_raw_decode(&msg, &packet);
                      cout << "thruster: " << packet.servo1_raw << " " << packet.servo3_raw << endl; 
                  }
                  // Add cases for other message types as needed
                  default:
                      // Handle unsupported message types or skip them
                      break;
              }
          }
      }
}

void M300::setBaudRate(){
    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    //if (tcgetattr(pik_port, &tty) != 0) {
  //      cerr << "Failed to get serial port attributes." << endl;
      //  close(pik_port);
    //}

    cfsetospeed(&tty, B115200);  // Set baud rate (57600 in this example)
    cfsetispeed(&tty, B115200);
    tty.c_cflag |= (CLOCAL | CREAD);  // Enable receiver and set local mode
    tty.c_cflag &= ~CSIZE;            // Mask the character size bits
    tty.c_cflag |= CS8;               // 8-bit data
    tty.c_cflag &= ~PARENB;           // No parity
    tty.c_cflag &= ~CSTOPB;           // 1 stop bit

    if (tcsetattr(pik_port, TCSANOW, &tty) != 0) {
//        cerr << "Failed to set serial port attributes." << endl;
        close(pik_port);
    }
}



//---------------------------------------------------------
// Constructor()
//
M300::M300()
{
  std::fstream serial;
  // Configuration variables  (overwritten by .moos params)
  m_max_rudder   = 30.0;        // default MAX_RUDDER (+/-)
  m_max_thrust   = 100.0;       // default MAX_THRUST (+/-)
  m_drive_mode   = "normal";    // default DRIVE_MODE ("normal"|"aggro"|"rotate")

  m_ivp_allstop      = true;
  m_moos_manual_override = true;

  // Stale Message Detection
  m_stale_check_enabled = false;
  m_stale_mode          = false;
  m_stale_threshold     = 1.5;
  m_count_stale         = 0;
  m_tstamp_des_rudder   = 0;
  m_tstamp_des_thrust   = 0;
  m_tstamp_compass_msg  = 0;

  m_num_satellites      = 0;
  m_batt_voltage        = 0;
  m_bad_nmea_semantic   = 0;

  m_nav_x   = -1;
  m_nav_y   = -1;
  m_nav_hdg = -1;
  m_nav_spd = -1;

  m_heading_source        = "auto";
  m_stale_gps_msg_thresh  = 1.5;
  m_last_gps_msg_time     = 0;

  m_nav_prefix      = "NAV";
  m_gps_prefix      = "GPS";
  m_compass_prefix  = "COMPASS";
  m_gps_blocked     = false;

  m_publish_body_vel = false;
  m_use_nvg_msg_for_nav_x_nav_y = false; 
  m_stale_compass_thresh = 1.0;
  m_declination = 0;
  m_fault_factor_thr_L = 1.0;
  m_fault_factor_thr_R = 1.0;
  m_fault_bias_thr_L = 0.0;
  m_fault_bias_thr_R = 0.0;
  m_fault_factor_rudder = 1.0;
  m_add_thruster_fault = false;
  m_rudder_bias_L = 0.0;
  m_rudder_bias_R = 0.0;  
  
  serialPort = "/dev/cu.usbserial-0001";
}

//---------------------------------------------------------
// Destructor()

M300::~M300()
{
  close(pik_port);
}

//---------------------------------------------------------
// Procedure: OnStartUp()

bool M300::OnStartUp()
{

  AppCastingMOOSApp::OnStartUp();
  //------------------------------------------------------
  // HANDLE PARAMETERS IN .MOOS FILE ---------------------
  //------------------------------------------------------
  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for (p = sParams.begin(); p != sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = tolower(biteStringX(line, '='));
    string value = line;

    bool handled = false;

   if((param == "port") && isNumber(value)) {
      int port = atoi(value.c_str());
      handled = m_ninja.setPortNumber(port);
    }
    else if(param == "ip_addr")
      handled = m_ninja.setIPAddr(value);
    else if(param == "comms_type") {
      serialPort = value;
      handled = true;
    }
    else if(param == "ivp_allstop")
      handled = setBooleanOnString(m_ivp_allstop, value);
    else if(param == "stale_check_enabled")
      handled = setBooleanOnString(m_stale_check_enabled, value);
    else if(param == "stale_thresh")
      handled = setPosDoubleOnString(m_stale_threshold, value);
    else if(param == "max_rudder")
      handled = m_thrust.setMaxRudder(value);
    else if(param == "max_thrust")
      handled = m_thrust.setMaxThrust(value);
    else if(param == "drive_mode"){
      handled = m_thrust.setDriveMode(value);
      m_drive_mode = value;
    }
    else if(param == "ignore_msg") 
      handled = handleConfigIgnoreMsg(value);
    else if(param == "heading_source"){
      if (value == "gps") {
  m_heading_source = "gps";
  handled = true;
      } else if (value == "imu") {
  m_heading_source = "imu";
  handled = true;
      } else if (value == "auto") {
  m_heading_source = "auto";
  handled = true;
      }
    }
    else if(param == "stale_gps_msg_thresh")
      handled = setPosDoubleOnString(m_stale_gps_msg_thresh, value);
    else if(param == "nav_prefix") { 
      if(!strContainsWhite(value)) {m_nav_prefix=value; handled=true;}
    }
    else if(param == "gps_prefix") { 
      if(!strContainsWhite(value)) {m_gps_prefix=value; handled=true;}
    }
    else if(param == "compass_prefix") { 
      if(!strContainsWhite(value)){m_compass_prefix=value; handled=true;}
    }
    else if (param == "publish_body_vel")  {
      handled = setBooleanOnString(m_publish_body_vel, value);
    }
    else if (param == "use_nvg_msg_for_nav_x_nav_y")  {
      handled = setBooleanOnString(m_use_nvg_msg_for_nav_x_nav_y, value);
    }
    else if (param == "stale_compass_thresh"){
      handled = setPosDoubleOnString(m_stale_compass_thresh, value);
    }
    else if (param == "fault_factor_thruster_l"){
      handled = setDoubleOnString(m_fault_factor_thr_L, value);
    }
    else if (param == "fault_factor_thruster_r"){
      handled = setDoubleOnString(m_fault_factor_thr_R, value);
    }
    else if (param == "fault_bias_thruster_l"){
      handled = setDoubleOnString(m_fault_bias_thr_L, value);
    }
    else if (param == "fault_bias_thruster_r"){
      handled = setDoubleOnString(m_fault_bias_thr_R, value);
    }
    else if (param == "add_thruster_fault_factor"){
      handled = setBooleanOnString(m_add_thruster_fault, value);
    }
    else if (param == "mag_declination_deg"){
      handled = setDoubleOnString(m_declination, value);
    }
    if(!handled){
      reportUnhandledConfigWarning(orig);
      list<string> warnings = m_thrust.getWarnings();
      while (!warnings.empty()){
        reportConfigWarning(warnings.front());
        warnings.pop_front();
      }
    }
  }
  
  // Init Geodesy 
  GeodesySetup();

  bool vnameOk = m_MissionReader.GetValue("Community", m_vname);
  if (!vnameOk) {
    reportUnhandledConfigWarning("Not able to get vehicle name");
  }
  
  registerVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool M300::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void M300::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("IVPHELM_ALLSTOP", 0);
  Register("DESIRED_THRUST",  0);
  Register("DESIRED_RUDDER",  0);
  Register("BLOCK_GPS",  0);
  Register("ROTATE_IN_PLACE", 0);
  Register("ROTATE_HDG_TARGET", 0);
  Register("ROTATE_TO_POINT", 0);
  Register("MOOS_MANUAL_OVERRIDE", 0);
  // Sim fault related. 
  Register("REQ_THRUSTER_R",0);
  Register("REQ_THRUSTER_L",0);
  Register("SIM_THR_FAULT_R",0);
  Register("SIM_THR_FAULT_L",0);
  Register("SIM_THR_SYM_BIAS",0);
  Register("SIM_THR_ROT_BIAS",0);
  Register("SIM_THR_L_BIAS",0);
  Register("SIM_THR_R_BIAS",0);
  Register("SIM_RUDDER_FAULT", 0);

  
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool M300::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);
  
  MOOSMSG_LIST::iterator p;
  STRING_LIST::iterator s;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    double mtime  = msg.GetTime();
    string key    = msg.GetKey();
    double dval   = msg.GetDouble();
    string sval   = msg.GetString();
    
#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity(); 
    string msrc  = msg.GetSource();  
#endif

   
    if(key == "IVPHELM_ALLSTOP")
      m_ivp_allstop = (toupper(sval) != "CLEAR");
    
    if(key == "comms_type") {
      serialPort = sval;
    }
    else if (key == "DESIRED_RUDDER" ){
      if ( m_thrust.getDriveMode() != "direct" ) {
  m_tstamp_des_rudder = mtime;
  m_thrust.setRudder(dval);
      }
    }
    else if (key == "DESIRED_THRUST") {
      if ( m_thrust.getDriveMode() != "direct" ) {
  m_tstamp_des_thrust = mtime;
  m_thrust.setThrust(dval);
  Notify("M3_DEBUG", m_thrust.getThrust());
      }
    }

    else if(key == "REQ_THRUSTER_R") {
      m_tstamp_des_thrust = mtime; // repurposed here, but same logic applies
      m_thrust.setThrusterSpeed(dval, "right");
    }

    else if(key == "REQ_THRUSTER_L") {
      m_tstamp_des_rudder = mtime; // repurposed here, but same logic applies
      m_thrust.setThrusterSpeed(dval, "left");
    }
    else if(key == "SIM_THR_FAULT_L") {
      if(m_add_thruster_fault){
  m_fault_factor_thr_L = dval;
  sendPulse();
      }
    }
    else if(key == "SIM_THR_FAULT_R") {
      if(m_add_thruster_fault){
  m_fault_factor_thr_R = dval;
  sendPulse();
      }
    }
    else if(key == "SIM_THR_SYM_BIAS") {
      if(m_add_thruster_fault){
  m_fault_bias_thr_L = dval;
  m_fault_bias_thr_R = dval;
  sendPulse();
      }
    }
    else if(key == "SIM_THR_ROT_BIAS") {
      if(m_add_thruster_fault){
  m_fault_bias_thr_L = dval;
  m_fault_bias_thr_R = -dval;
  sendPulse();
      }
    }

    else if(key == "SIM_THR_L_BIAS") {
      if(m_add_thruster_fault){
  m_fault_bias_thr_L = dval;
  //sendPulse();
      }
    }
    else if(key == "SIM_THR_R_BIAS") {
      if(m_add_thruster_fault){
  m_fault_bias_thr_R = dval;
  //sendPulse();
      }
    }

    else if (key == "SIM_RUDDER_FAULT") {
      if (m_add_thruster_fault) {
        m_fault_factor_rudder = dval;
        sendPulse();
      }
    }

    else if(key == "BLOCK_GPS") 
      setBooleanOnString(m_gps_blocked, sval);
    else if(key == "ROTATE_IN_PLACE") {      
      bool bval, ok1;
      ok1 = setBooleanOnString(bval, sval);
      m_rot_ctrl.setRotateInPlace(bval);
      
      if (ok1 && bval ) {
  // Record the time and location
  m_rot_ctrl.setCmdTimeStamp(mtime);
  m_rot_ctrl.setStartRotX(m_nav_x);
  m_rot_ctrl.setStartRotY(m_nav_y);
      }
    }
    else if(key == "ROTATE_HDG_TARGET") {
      m_rot_ctrl.setHeadingTarget(dval);
    }
    else if(key == "ROTATE_TO_POINT") {
      // save the current location for calculation
      m_rot_ctrl.setStartRotX(m_nav_x);
      m_rot_ctrl.setStartRotY(m_nav_y);
      
      bool ok2 = m_rot_ctrl.handlePoint(sval);
      if (ok2)
  Notify("ROTATE_HDG_TARGET", m_rot_ctrl.getHeadingTarget() );  // for debugging. 
      
    }
    else if(key == "MOOS_MANUAL_OVERRIDE") {
      setBooleanOnString(m_moos_manual_override, sval);

    }
    
    else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);


  }
  return(true);
}


//---------------------------------------------------------
// Procedure: Iterate()

bool M300::Iterate()
{
  AppCastingMOOSApp::Iterate();
  
  // Part 1: Check for allstop or staleness
  checkForStalenessOrAllStop();
    
  // Part 2: Connect if needed, and write/read from socket
  // std::cout << serialPort << std::endl;
  // pik_port = open(serialPort.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
  m_ninja.setCommsType("client");
  //setBaudRate();


  if(pik_port >= 0) {
      sendMessagesToSocket();
      receiveComm();
  }
  else{
    fakeGPS();
    pik_port = open(serialPort.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    setBaudRate();
    cout << "not open!" << endl;
  }

  // Part 3: Get Appcast events from ninja and report them
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: GeodesySetup()
//   Purpose: Initialize geodesy object with lat/lon origin.
//            Used for LatLon2LocalUTM conversion.

bool M300::GeodesySetup()
{
  double LatOrigin = 0.0;
  double LonOrigin = 0.0;

  // Get Latitude Origin from .MOOS Mission File
  bool latOK = m_MissionReader.GetValue("LatOrigin", LatOrigin);
  if(!latOK) {
    reportConfigWarning("Latitude origin missing in MOOS file.");
    return(false);
  }

  // Get Longitude Origin from .MOOS Mission File
  bool lonOK = m_MissionReader.GetValue("LongOrigin", LonOrigin);
  if(!lonOK){
    reportConfigWarning("Longitude origin missing in MOOS file.");
    return(false);
  }

  // Initialise CMOOSGeodesy object
  bool geoOK = m_geodesy.Initialise(LatOrigin, LonOrigin);
  if(!geoOK) {
    reportConfigWarning("CMOOSGeodesy::Initialise() failed. Invalid origin.");
    return(false);
  }

  return(true);
}

//---------------------------------------------------------
// Procedure: sendMessagesToSocket()

void M300::sendMessagesToSocket()
{

  double thrustL, thrustR;

  // Mode 1:  Rotation

  // Check if still ok to rotate in place
  bool ok_to_rotate = m_rot_ctrl.checkClearToRotate( m_nav_x, m_nav_y, m_curr_time);

  if (ok_to_rotate and !m_moos_manual_override) {

    // overwrite incoming thrust and rudder commands
    double thrust, rudder;
    m_rot_ctrl.calControl(m_nav_hdg, m_nav_x, m_nav_y, thrust, rudder);

    // Check if finished
    bool rot_finished = m_rot_ctrl.checkRotateFinished(m_nav_hdg);
    // If finished, and the command to rotate is still true,
    // then send the ROTATE_FINISHED end flag.
    if ( rot_finished and m_rot_ctrl.getRotateInPlace() )
      Notify("ROTATE_FINISHED", "true");
    
    m_thrust.setRudder(rudder * m_max_rudder);
    m_thrust.setThrust(thrust * m_max_thrust);

    // use rotate mode for thrusters. 
    m_thrust.setDriveMode("rotate");
    
  } else {

    // Mode 2: Carry on as normal
    m_thrust.setDriveMode(m_drive_mode);

  }

  // Calculate the right and left thruster values
  // with whatever DriveMode is selected.
  m_thrust.calcDiffThrust();
  // Update differential thrust values
  thrustL = m_thrust.getThrustLeft();
  thrustR = m_thrust.getThrustRight();

  // cout << "Thrust: " << thrustL << " " << thrustR << endl;
  
  sendServo(3, thrustL);
  sendServo(1, thrustR);

  double thrustL_faulty = 0.0;
  double thrustR_faulty = 0.0; 
  
  // Update the thruster values if we are simulated a fault
  if (m_add_thruster_fault){
    calculateFaultyThrust(thrustL, thrustR, thrustL_faulty, thrustR_faulty);

  }
  // Send the primary PYDIR front seat command
  // FALCON Project:  Add a simulated thruster fault
  // if requested
  
  string msg = "PYDIR,";
  if (m_add_thruster_fault)
    msg += doubleToStringX(thrustL_faulty, 1) + ",";
  else
    msg += doubleToStringX(thrustL, 1) + ",";

  if (m_add_thruster_fault)
    msg += doubleToStringX(thrustR_faulty, 1);
  else
    msg += doubleToStringX(thrustR, 1);

  msg = "$" + msg + "*" + checksumHexStr(msg) + "\r\n";

  // m_ninja.sendSockMessage(msg);

  // Publish command to MOOSDB for logging/debugging
  if (m_add_thruster_fault)
  {
    Notify("PYDIR_THRUST_L_ACTUAL", thrustL_faulty);
    Notify("PYDIR_THRUST_R_ACTUAL", thrustR_faulty);
  }
   
  Notify("PYDIR_THRUST_L", thrustL);
  Notify("PYDIR_THRUST_R", thrustR);

}

//---------------------------------------------------------
// Procedure: readMessagesFromSocket()
//      Note: Messages returned from the SockNinja have been
//            confirmed to be valid NMEA format and checksum

void M300::readMessagesFromSocket()
{

  string line = "";
  std::getline(serial, line);

    //cout << line << endl;

    string msg = line;
    Notify("IM300_RAW_NMEA", msg);

    bool handled = false;
    if(m_ignore_msgs.count(msg.substr (0,6)) >= 1) 
      handled = true;
    else if(strBegins(msg, "$GPRMC"))
      handled = handleMsgGPRMC(msg);
    else if(strBegins(msg, "$GNRMC"))
      handled = handleMsgGNRMC(msg); // Added on 06-01-2022 by Supun for 2022 Herons
    else if(strBegins(msg, "$GPGGA"))
      handled = handleMsgGPGGA(msg);
    else if(strBegins(msg, "$GNGGA"))
      handled = handleMsgGNGGA(msg); // Added on 06-01-2022 by Supun for 2022 Herons
    else if(strBegins(msg, "$CPNVG")){

      bool cond1 = m_heading_source == "imu";
      bool cond2 = m_heading_source == "auto";
      // check if using gps or ekf position from the front seat
      if (m_use_nvg_msg_for_nav_x_nav_y)
  handled = handleMsgCPNVG(msg); 
      else if (cond1 or cond2)
  handled = handleMsgCPNVG_heading(msg);  // Only using NVG for low speed heading!
      else   // ignore it
  handled = true;
    }
    else if(strBegins(msg, "$CPRBS"))
      handled = handleMsgCPRBS(msg);
    
    else if(strBegins(msg, "$CPRCM")){
      if (m_publish_body_vel)
  handled = handleMsgCPRCM(msg);
      else
  handled = true;
    }
    else if(strBegins(msg, "$CPNVR")){
      if (m_publish_body_vel)
  handled = handleMsgCPNVR(msg);
      else
  handled = true;
    }
    else
      reportBadMessage(msg, "Unknown NMEA Key");
            
    if(!handled)
      m_bad_nmea_semantic++;
  
}

//---------------------------------------------------------
// Procedure: handleConfigIgnoreMsg()
//  Examples: ignore_msg = $GPGLL
//            ignore_msg = $GPGLL, GPGSV, $GPVTG

bool M300::handleConfigIgnoreMsg(string str)
{
  bool all_ok = true;
  
  vector<string> msgs = parseString(str, ',');
  for(unsigned int i=0; i<msgs.size(); i++) {
    string msg = stripBlankEnds(msgs[i]);
    // Check if proper NMEA Header
    if((msg.length() == 6) && (msg.at(0) = '$'))
      m_ignore_msgs.insert(msg);
    else
      all_ok = false;
  }

  return(all_ok);
}

//---------------------------------------------------------
// Procedure: checkForStalenessOrAllStop()
//   Purpose: If DESIRED_RUDDER or _THRUST commands are stale,
//            set local desired_rudder/thrust to zero.
//            If an all-stop has been posted, also set the
//            local desired_rudder/thrust vals to zero.

void M300::checkForStalenessOrAllStop()
{
  if(m_ivp_allstop) {
    m_thrust.setRudder(0);
    m_thrust.setThrust(0);
    if ( m_thrust.getDriveMode() == "direct" ) {
      m_thrust.setThrusterSpeed(0.0, "right");
      m_thrust.setThrusterSpeed(0.0, "left");
    }
    return;
  }

  // If not checking staleness, ensure stale mode false, return.
  if(!m_stale_check_enabled) {
    m_stale_mode = false;
    return;
  }

  double lag_rudder = m_curr_time - m_tstamp_des_rudder;
  double lag_thrust = m_curr_time - m_tstamp_des_thrust;

  bool stale_rudder = (lag_rudder > m_stale_threshold);
  bool stale_thrust = (lag_thrust > m_stale_threshold);

  if(stale_rudder)
    m_count_stale++;
  if(stale_thrust)
    m_count_stale++;

  bool stale_mode = false;
  if(stale_rudder || stale_thrust) {
    m_thrust.setRudder(0);
    m_thrust.setThrust(0);
    stale_mode = true;
  }

  // Check new stale_mode represents a change from previous
  if(stale_mode && !m_stale_mode) 
    reportRunWarning("Stale Command Detected: Stopping Vehicle");
  if(!stale_mode && m_stale_mode) 
    retractRunWarning("Stale Command Detected: Stopping Vehicle");

  m_stale_mode = stale_mode;
}


//---------------------------------------------------------
// Procedure: handleMsgGPRMC()
//      Note: Proper NMEA format and checksum prior confirmed  
//   Example:
//   $GPRMC,150942.619,A,0000.00,N,00000.00,W,1.1663,0,291263,0,E*41

//  0   $GPRMC
//  1 [Timestamp]    UTC of position fix
//  2 [Data status]  A-ok, V-invalid
//  3 [Lat_NMEA]     Calculated latitude, in NMEA format
//  4 [LatNS_NMEA]   Hemisphere (N or S) of latitude
//  5 [Lon_NMEA]     Calculated longitude, in NMEA format
//  6 [LonEW_NMEA]   Hemisphere (E or W) of longitude
//  7 [Speed]        Speed over ground in Knots
//  8 [Course]       True Course, Track made good in degrees
//  9 [DepthTop]     Date of Fix
// 10 [Mag Var]      Magnetic variation degrees
// 11 [Mag Var E/W]  Easterly subtracts from true course



bool M300::handleMsgGPRMC(string msg)
{
  if(!strBegins(msg, "$GPRMC,"))
    return(false);

  // Remove the checksum info from end
  rbiteString(msg, '*');

  vector<string> flds = parseString(msg, ',');
  if(flds.size() != 13) {
    return(reportBadMessage(msg, "Wrong field count"));
  } 
  
  if((flds[4] != "N") && (flds[4] != "S"))
    return(reportBadMessage(msg, "Bad N/S Hemisphere"));
  if((flds[6] != "W") && (flds[4] != "E"))
    return(reportBadMessage(msg, "Bad E/W Hemisphere"));
  
  string str_lat = flds[3];
  string str_lon = flds[5];
  string str_kts = flds[7];
  string str_hdg = flds[8];
  if(!isNumber(str_lat))
    return(reportBadMessage(msg, "Bad Lat"));
  if(!isNumber(str_lon))
    return(reportBadMessage(msg, "Bad Lon"));
  // New GPS modules fail to send speed and heading
  // sometimes when the GPS signal is poor.
  // Moving these checks below for now
  // extra warnings/ 

  if (!m_use_nvg_msg_for_nav_x_nav_y) {
    double dbl_lat = latDDMMtoDD(str_lat);
    double dbl_lon = lonDDDMMtoDDD(str_lon);
    if(flds[4] == "S")
      dbl_lat = -dbl_lat;
    if(flds[6] == "W")
      dbl_lon = -dbl_lon;
    Notify(m_nav_prefix+"_LAT", dbl_lat, "GPRMC");
    Notify(m_nav_prefix+"_LON", dbl_lon, "GPRMC");
    Notify(m_nav_prefix+"_LONG", dbl_lon, "GPRMC");
    if (!m_gps_blocked){
      Notify(m_gps_prefix+"_LAT", dbl_lat, "GPRMC");
      Notify(m_gps_prefix+"_LON", dbl_lon, "GPRMC");
      Notify(m_gps_prefix+"_LONG", dbl_lon, "GPRMC");
    }
    
    double x, y;
    bool ok = m_geodesy.LatLong2LocalGrid(dbl_lat, dbl_lon, y, x);
    if(ok) {
      m_nav_x = x;
      m_nav_y = y;
      Notify(m_nav_prefix+"_X", x, "GPRMC");
      Notify(m_nav_prefix+"_Y", y, "GPRMC");
      if (!m_gps_blocked){
  Notify(m_gps_prefix+"_X", x, "GPRMC");
  Notify(m_gps_prefix+"_Y", y, "GPRMC");
      }
    }
  }
  
  if(isNumber(str_kts)) {
    double dbl_kts = atof(str_kts.c_str());
    double dbl_mps = dbl_kts * 0.514444;
    dbl_mps = snapToStep(dbl_mps, 0.05);
    m_nav_spd = dbl_mps;
    Notify(m_nav_prefix+"_SPEED", dbl_mps, "GPRMC");
  }

  if(isNumber(str_hdg)) {
    double dbl_hdg = atof(str_hdg.c_str());
    if (( m_heading_source == "gps" ) or ( m_heading_source == "auto")) {
      m_nav_hdg = dbl_hdg;
      Notify(m_nav_prefix+"_HEADING", dbl_hdg, "GPRMC");
    } else{
      Notify("GPS_HEADING", dbl_hdg, "GPRMC");
      Notify("GPS_HEADING", dbl_hdg, "GPRMC");
    }
    m_last_gps_msg_time = MOOSTime();
  }
  return(true);
}


//---------------------------------------------------------
// Procedure: handleMsgGNRMC()
bool M300::handleMsgGNRMC(string msg)
{
  if(!strBegins(msg, "$GNRMC,"))
    return(false);

  // Remove the checksum info from end
  rbiteString(msg, '*');

  vector<string> flds = parseString(msg, ',');
  if(flds.size() != 13){
    return(reportBadMessage(msg, "Wrong field count"));
  } 
  
  if((flds[4] != "N") && (flds[4] != "S"))
    return(reportBadMessage(msg, "Bad N/S Hemisphere"));
  if((flds[6] != "W") && (flds[4] != "E"))
    return(reportBadMessage(msg, "Bad E/W Hemisphere"));
  
  string str_lat = flds[3];
  string str_lon = flds[5];
  string str_kts = flds[7];
  string str_hdg = flds[8];
  if(!isNumber(str_lat))
    return(reportBadMessage(msg, "Bad Lat"));
  if(!isNumber(str_lon))
    return(reportBadMessage(msg, "Bad Lon"));

  // check if using gps or ekf position from the front seat
  if (!m_use_nvg_msg_for_nav_x_nav_y) {
    double dbl_lat = latDDMMtoDD(str_lat);
    double dbl_lon = lonDDDMMtoDDD(str_lon);
    if(flds[4] == "S")
      dbl_lat = -dbl_lat;
    if(flds[6] == "W")
      dbl_lon = -dbl_lon;
    Notify(m_nav_prefix+"_LAT", dbl_lat, "GNRMC");
    Notify(m_nav_prefix+"_LON", dbl_lon, "GNRMC");
    Notify(m_nav_prefix+"_LONG", dbl_lon, "GNRMC");
    if (!m_gps_blocked){
      Notify(m_gps_prefix+"_LAT", dbl_lat, "GNRMC");
      Notify(m_gps_prefix+"_LON", dbl_lon, "GNRMC");
      Notify(m_gps_prefix+"_LONG", dbl_lon, "GNRMC");
    }
    
    double x, y;
    bool ok = m_geodesy.LatLong2LocalGrid(dbl_lat, dbl_lon, y, x);
    if(ok) {
      m_nav_x = x;
      m_nav_y = y;
      Notify(m_nav_prefix+"_X", x, "GNRMC");
      Notify(m_nav_prefix+"_Y", y, "GNRMC");
      if (!m_gps_blocked){
  Notify(m_gps_prefix+"_X", x, "GNRMC");
  Notify(m_gps_prefix+"_Y", y, "GNRMC");
      }
    }
  }
  
  if(isNumber(str_kts)) {
    double dbl_kts = atof(str_kts.c_str());
    double dbl_mps = dbl_kts * 0.514444;
    dbl_mps = snapToStep(dbl_mps, 0.01);
    m_nav_spd = dbl_mps;
    Notify(m_nav_prefix+"_SPEED", dbl_mps, "GNRMC");
  } else {
    return(reportBadMessage(msg, "Bad Kts"));
  }
  
  if(isNumber(str_hdg)) {
    double dbl_hdg = atof(str_hdg.c_str());
    if (( m_heading_source == "gps" ) or ( m_heading_source == "auto")) {
      m_nav_hdg = dbl_hdg;
      Notify(m_nav_prefix+"_HEADING", dbl_hdg, "GPRMC");
    } else{
      Notify("GPS_HEADING", dbl_hdg, "GPRMC");
    }
    m_last_gps_msg_time = MOOSTime();
  } 
  
  return(true);
}


//---------------------------------------------------------
// Procedure: handleMsgGPGGA()
//      Note: Proper NMEA format and checksum prior confirmed  
//      Note: Only grabbing the number of satellites from this msg
//   Example:
//   $GPGGA,150502.00,4221.46039,N,07105.28402,W,2,11,0.98,5.5,M,-33.2,M,,0000*62
//                                                 ^^
//  0   $GPGGA
//  1 [Timestamp]    UTC of position fix
//  2 [Lat_NMEA]     Calculated latitude, in NMEA format
//  3 [LatNS_NMEA]   Hemisphere (N or S) of latitude
//  4 [Lon_NMEA]     Calculated longitude, in NMEA format
//  5 [LonEW_NMEA]   Hemisphere (E or W) of longitude
//  6 [GPS Qual]     (0=invalid; 1=GPS fix; 2=Diff. GPS fix)
//  7 [Num Sats]     Num satellites in use, not those in view
//  8 [Horz Dilu]    Horizontal dilution of position
//  9 [Ant Alt]      Antenna altitude above/below mean sea level (geoid)
// 10 [Ant Units]    Meters  (Antenna height unit)
// 11 [Geo Sep]      Geoidal separation (Diff. between WGS-84 earth
//                   ellipsoid and mean sea level.
// 12 [GS Units]     Meters  (Units of geoidal separation)
// 13 [Age]          in secs since last update from diff. ref station
// 14 [Diff ID]     Diff. reference station ID#


bool M300::handleMsgGPGGA(string msg)
{
  if(!strBegins(msg, "$GPGGA,"))
    return(false);

  // Remove the checksum info from end
  rbiteString(msg, '*');

  vector<string> flds = parseString(msg, ',');
  if(flds.size() != 14) {
    return(reportBadMessage(msg, "Wrong field count"));
  }
  
  string str_sats = flds[7];
  if(!isNumber(str_sats))
    return(reportBadMessage(msg, "Bad Sats"));
  
  int int_sats = atoi(str_sats.c_str());
  Notify("GPS_SATS", int_sats, "GPGGA");

  if(int_sats < 0)
    int_sats = 0;
  m_num_satellites = (unsigned int)(int_sats);
  
  return(true);
}


//---------------------------------------------------------
// Procedure: handleMsgGNGGA()
bool M300::handleMsgGNGGA(string msg)
{
  if(!strBegins(msg, "$GNGGA,"))
    return(false);

  // Remove the checksum info from end
  rbiteString(msg, '*');

  vector<string> flds = parseString(msg, ',');
  if(flds.size() != 14){
    return(reportBadMessage(msg, "Wrong field count"));
  }
  
  string str_sats = flds[7];
  if(!isNumber(str_sats))
    return(reportBadMessage(msg, "Bad Sats"));
  
  int int_sats = atoi(str_sats.c_str());
  Notify("GPS_SATS", int_sats, "GNGGA");

  if(int_sats < 0)
    int_sats = 0;
  m_num_satellites = (unsigned int)(int_sats);
  
  return(true);
}


//---------------------------------------------------------
// Procedure: handleMsgCPNVG()
//      Note: Proper NMEA format and checksum prior confirmed  
//   Example:
//   $CPNVG,160743.715,0000.00,N,00000.00,W,1,,,0,,,160743.715*64
//      0      1         2     3   4      5 6   9      12
//
//  0   CPNVG
//  1 [Timestamp]    Timestamp of the sentence
//  2 [Lat_NMEA]     Calculated latitude, in NMEA format
//  3 [LatNS_NMEA]   Hemisphere (N or S) of latitude
//  4 [Lon_NMEA]     Calculated longitude, in NMEA format
//  5 [LonEW_NMEA]   Hemisphere (E or W) of longitude
//  6 [PosQual]      Quality of position est (no GPS=0, otherwise=1)
//  7 [AltBottom]    Alt in meters from bottom, blank for USVs
//  8 [DepthTop]     Dep in meters from top, blank for USVs
//  9 [Heading]      Dir of travel in degs clockwise from true north
// 10 [Roll]         Degrees of roll
// 11 [Pitch]        Degrees of pitch
// 12 [NavTimestamp] Timestamp for time this pose/position

bool M300::handleMsgCPNVG(string msg)
{
  if(!strBegins(msg, "$CPNVG,"))
    return(false);
  
  // Remove the checksum info from end
  rbiteString(msg, '*');
  vector<string> flds = parseString(msg, ',');
  if(flds.size() != 13) {
    return(reportBadMessage(msg, "Wrong field count"));
  }
  
  if((flds[3] != "N") && (flds[3] != "S"))
    return(reportBadMessage(msg, "Bad N/S Hemisphere"));
  if((flds[5] != "W") && (flds[5] != "E")) 
    return(reportBadMessage(msg, "Bad E/W Hemisphere"));
  
  string str_lat = flds[2];
  string str_lon = flds[4];
  string str_hdg = flds[9];
  if(!isNumber(str_lat))  
    return(reportBadMessage(msg, "Bad Lat"));
  if(!isNumber(str_lon)) 
    return(reportBadMessage(msg, "Bad Lon"));
  if(!isNumber(str_hdg)) 
    return(reportBadMessage(msg, "Bad Hdg"));
  
  double dbl_lat = latDDMMtoDD(str_lat);
  double dbl_lon = lonDDDMMtoDDD(str_lon);
  if(flds[3] == "S")
    dbl_lat = -dbl_lat;
  if(flds[5] == "W")
    dbl_lon = -dbl_lon;
  Notify(m_nav_prefix+"_LAT", dbl_lat, "CPNVG");
  Notify(m_nav_prefix+"_LON", dbl_lon, "CPNVG");
  Notify(m_nav_prefix+"_LONG", dbl_lon, "CPNVG");

  double x, y;
  bool ok = m_geodesy.LatLong2LocalGrid(dbl_lat, dbl_lon, y, x);
  if(ok) {
    m_nav_x = x;
    m_nav_y = y;
    Notify(m_nav_prefix+"_X", x, "CPNVG");
    Notify(m_nav_prefix+"_Y", y, "CPNVG");
  }
  
  double dbl_hdg = atof(str_hdg.c_str());
  m_nav_hdg = dbl_hdg;
  Notify(m_nav_prefix+"_HEADING", dbl_hdg, "CPNVG");
  Notify(m_compass_prefix+"_HEADING", dbl_hdg, "CPNVG");

  // Send out full state position message
  if(m_publish_body_vel){
    string str_nav_x = doubleToStringX(m_nav_x, 4);
    string str_nav_y = doubleToStringX(m_nav_y, 4);

    bool stale = (MOOSTime() - m_tstamp_compass_msg) >  m_stale_threshold;
    string str_state_hdg; 
    if (!stale) {
      str_state_hdg = doubleToStringX(m_compass_hdg); 
    } else {
      str_state_hdg = doubleToStringX(m_nav_hdg);
    }
    string nav_full_pos_msg = "x(" + str_nav_x + ")y(" + str_nav_y + ")hdg(" + str_state_hdg + ")";
    Notify("NAV_FULL_POS", nav_full_pos_msg, "CPNVG");

    // Also send for UNREP coordination
    NodeMessage node_message;
    
    node_message.setSourceNode(m_vname);
    node_message.setDestNode("all");
    node_message.setVarName("NAV_FULL_POS_" + m_vname);
    node_message.setStringVal(nav_full_pos_msg);
    node_message.setColor("invisible");
    string n_msg = node_message.getSpec();
    
    Notify("NODE_MESSAGE_LOCAL", n_msg); 
    
  }
  return(true);
}

//---------------------------------------------------------
// Procedure: handleMsgCPNVG_heading()
//      Note: Proper NMEA format and checksum prior confirmed  
// This function will only publish NAV_HEADING from the 
// $CPNVG message

bool M300::handleMsgCPNVG_heading(string msg)
{
  if(!strBegins(msg, "$CPNVG,"))
    return(false);
  
  // Remove the checksum info from end
  rbiteString(msg, '*');
  vector<string> flds = parseString(msg, ',');
  if(flds.size() != 13) {
    string warning = "Wrong field count:" + uintToString(flds.size());      
    return(reportBadMessage(msg, warning));
    
  }
  
  string str_hdg = flds[9];
  if(!isNumber(str_hdg)) 
    return(reportBadMessage(msg, "Bad Hdg"));  

  double dbl_hdg = atof(str_hdg.c_str());

  bool stale_gps = ( (MOOSTime() - m_last_gps_msg_time) > m_stale_gps_msg_thresh );
  if ( (m_heading_source == "imu") or ( (m_heading_source == "auto") and stale_gps ) ){
    m_nav_hdg = dbl_hdg;
    Notify(m_nav_prefix+"_HEADING", dbl_hdg, "CPNVG");
  }
  Notify(m_compass_prefix+"_HEADING", dbl_hdg, "CPNVG");
  
  return(true);
}


//---------------------------------------------------------
// Procedure: handleMsgCPRBS()
//      Note: Proper NMEA format and checksum prior confirmed  
//   Example: $CPRBS,091945.064,1,15.2,15.1,15.3,0*57
//               0      1       2   3   4    5   6 HH
//
//  0   CPRBS
//  1 [Timestamp]     Timestamp of the sentence.
//  2 [ID_Battery]    Unique ID of battery being reported on.
//  3 [V_Batt_Stack]  Voltage of the battery bank.
//  4 [V_Batt_Min]    Lowest voltage read from cells in bank.
//  5 [V_Batt_Max]    Highest voltage read from cells in bank. 
//  6 [TemperatureC]  Temperature in Celsius.

bool M300::handleMsgCPRBS(string msg)
{
  if(!strBegins(msg, "$CPRBS,"))
    return(false);
  
  // Remove the checksum info from end
  rbiteString(msg, '*');
  vector<string> flds = parseString(msg, ',');
  if(flds.size() != 7) {
    string warning = "Wrong field count:" + uintToString(flds.size());
    return(reportBadMessage(msg, warning));
  }
  
  string str_voltage = flds[3];
  if(!isNumber(str_voltage))
    return(reportBadMessage(msg, "Bad Voltage"));
  
  double dbl_voltage = atof(str_voltage.c_str());
  m_batt_voltage = dbl_voltage;
  Notify("M300_BATT_VOLTAGE", dbl_voltage, "CPRBS");
  return(true);
}


//---------------------------------------------------------
// Procedure: handleMsgCPRCM()
//      Note: Proper NMEA format and checksum prior confirmed
//   Example: $CPRCM,091945.044,1,344.0,0.1,0.2,434.4*CS
//               0       1,     2,  3,   4,  5,    6  HH
//  0   CPRCM
//  1 [Timestamp]    Timestamp of the sentence
//  2 [ID_Compass]   Unique ID number of the compass being reported on
//  3 [Heading]      Raw reading from compass for degrees clockwise from true north
//  4 [Pitch]        Raw reading from compass for degrees of pitch
//  5 [Roll]         Raw reading from compass for degrees of roll
//  6 [NavTimestamp] Timestamp for time compass reported this data. If blank, use [Timestamp]

bool M300::handleMsgCPRCM(string msg)
{
    if(!strBegins(msg, "$CPRCM,"))
    return(false);
  
  // Remove the checksum info from end
  rbiteString(msg, '*');
  vector<string> flds = parseString(msg, ',');
  if(flds.size() != 7) {
    string warning = "Wrong field count:" + uintToString(flds.size());
    return(reportBadMessage(msg, warning));
  }

  string str_compass_hdg = flds[3];
  if(!isNumber(str_compass_hdg))
    return(reportBadMessage(msg, "Bad compass heading"));
  
  double dbl_compass_hdg = atof(str_compass_hdg.c_str()) + m_declination;
  
  m_compass_hdg = dbl_compass_hdg;
  // clip it to [0 360]
  if (m_compass_hdg > 360)
    m_compass_hdg = m_compass_hdg - 360;
  if (m_compass_hdg < 0)
    m_compass_hdg = m_compass_hdg + 360;
    
  Notify("COMPASS_HEADING_RAW", m_compass_hdg , "CPRCM");
  
  m_tstamp_compass_msg = MOOSTime();
  return(true);
}





//---------------------------------------------------------
// Procedure: handleMsgCPNVR()
//      Note: Proper NMEA format and checksum prior confirmed
//   Example: $CPNVR,091945.064,0.3,0.4,0.1,2.1,1.3,3.4*CS
//                0      1       2   3   4   5   6   7  HH
//
//  0   CPNVR
//  1 [Timestamp]   Timestamp of the sentence
//  2 [Vel_East]    East component of vehicle transit velocity
//  3 [Vel_North]   North component of vehicle transit velocity
//  4 [Vel_Down]    Vertical component of vehicle transit velocity
//  5 [Rate_Pitch]  Deg/s of pitch rate
//  6 [Rate_Roll]   Deg/s of roll rate
//  7 [Rate_Yaw]    Deg/s of yaw rate
bool M300::handleMsgCPNVR(string msg)
{
  
  if(!strBegins(msg, "$CPNVR,"))
    return(false);
  
  // Remove the checksum info from end
  rbiteString(msg, '*');
  vector<string> flds = parseString(msg, ',');
  if(flds.size() != 7) {
    string warning = "Wrong field count:" + uintToString(flds.size());
    return(reportBadMessage(msg, warning));
  }
  
  //  Check that compass msg is good
  if ( (m_tstamp_compass_msg - MOOSTime() ) > m_stale_compass_thresh)
    return(reportBadMessage(msg, "Stale compass heading, not able to convert NVR message to body coordinates "));

  
  // convert to body coordinates using the last compass heading
  string str_vel_east  = flds[2];
  string str_vel_north = flds[3];
  string str_rate_yaw  = flds[7];

  // Error checking
  if(!isNumber(str_vel_east)){
    // 'nan' is reported in this field if the speed is close to 0
    // ( see documentation at http://wiki.ros.org/nmea_navsat_driver
    // Just set to 0 in this case
    bool cond1 = ((str_vel_east == "nan") && (fabs(m_nav_spd) <= 0.1));
    bool cond2 = ( m_nav_spd ==-1); // have not recieved a speed msg
    if (cond1 || cond2)
      str_vel_east = "0";
    else {
      //return(true);
      return(reportBadMessage(msg, "Bad easting velocity"));
    }
  }
  if(!isNumber(str_vel_north)){
    // Same as comment above
    bool cond1 = ((str_vel_north == "nan") && (fabs(m_nav_spd) <= 0.1));
    bool cond2 = ( m_nav_spd == -1); // have not recieved a speed msg
    if (cond1 || cond2)
      str_vel_north = "0";
    else {
      //return(true);
      return(reportBadMessage(msg, "Bad northing velocity"));
    }
  }
  if(!isNumber(str_rate_yaw))
    return(reportBadMessage(msg, "Bad yaw rate "));
  
  double dbl_vel_east  = atof(str_vel_east.c_str());
  double dbl_vel_north = atof(str_vel_north.c_str());
  double dbl_rate_yaw  = atof(str_rate_yaw.c_str());

  // Convert to body relative coords
  //  NED frame

  //             |  deg    /
  //             |  hdg   /
  //             |       /
  //             |      /
  //                   /  
  //        vel north / 
  //             ^   /
  //             |  / 
  //             | /
  //              /
  //            /*/ ------> vel east
  //          /***/
  //         /***/
  //        /***/
  //       /***/
  //       ----
  //

  // Body reference velocities, converted to the correct units
  double deg_to_rad = PI/180.0;
  double vel_surge = dbl_vel_north * cos(m_compass_hdg*deg_to_rad) + dbl_vel_east * sin(m_compass_hdg*deg_to_rad); 
  double vel_sway  = dbl_vel_north * -1.0*sin(m_compass_hdg*deg_to_rad) + dbl_vel_east * cos(m_compass_hdg*deg_to_rad);
  double dbl_rate_yaw_rad = deg_to_rad*dbl_rate_yaw;
  
  Notify("NAV_VEL_TWIST_LINEAR_X", vel_surge);
  Notify("NAV_VEL_TWIST_LINEAR_Y", vel_sway);
  Notify("NAV_VEL_TWIST_ANGULAR_Z",dbl_rate_yaw_rad);

  std::string unav_string = std::to_string(vel_surge);
  std::string unav_header = "u(";
  std::string vnav_string = std::to_string(vel_sway);
  std::string vnav_header = ")v(";
  std::string rnav_string = std::to_string(dbl_rate_yaw_rad);
  std::string rnav_header = ")r(";
  std::string end_char = ")";
  std::string nav_full_state = unav_header + unav_string + vnav_header + vnav_string + rnav_header + rnav_string + end_char;

  Notify("NAV_FULL_STATE", nav_full_state);
  
  // Also send for UNREP analysis
  NodeMessage node_message;

  node_message.setSourceNode(m_vname);
  node_message.setDestNode("all");
  node_message.setVarName("NAV_FULL_STATE_" + m_vname);
  node_message.setStringVal(nav_full_state);
  node_message.setColor("invisible");
  string n_msg = node_message.getSpec();
  
  Notify("NODE_MESSAGE_LOCAL", n_msg); 

  return(true);
}



//--------------------------------------------------------
// Procedure: sendPulse()
void M300::sendPulse() {
  XYRangePulse pulse;
  pulse.set_x(m_nav_x);                
  pulse.set_y(m_nav_y);                
  pulse.set_label("thruster_fault_pulse");
  pulse.set_rad(30.0);
  pulse.set_time(MOOSTime());       
  pulse.set_color("edge", "yellow");
  pulse.set_color("fill", "red");
  pulse.set_duration(6.0);

  string spec = pulse.get_spec();
  Notify("VIEW_RANGE_PULSE", spec);
  return; 
}



// -----------------------------------------------------------
// Procedure: calculateFaultyThrust
//            calculates the thrust values for each thruster by taking into
//            account the various fault factors.  The arguments are updated by
//            reference. 
void M300::calculateFaultyThrust(double thrustL, double thrustR, double &thrustL_faulty, double &thrustR_faulty)
{

  // Add a scaled rudder command as a bias on the left and right thruster
  m_rudder_bias_L = ( (m_fault_factor_rudder - 1.0) / 2.0 ) * (thrustL - thrustR);
  m_rudder_bias_R = ( (m_fault_factor_rudder - 1.0) / 2.0 ) * (thrustR - thrustL);

  thrustL_faulty = thrustL * m_fault_factor_thr_L + m_fault_bias_thr_L + m_rudder_bias_L;
  thrustR_faulty = thrustR * m_fault_factor_thr_R + m_fault_bias_thr_R + m_rudder_bias_R;

  return; 
}



//---------------------------------------------------------
// Procedure: reportBadMessage()
  
bool M300::reportBadMessage(string msg, string reason)
{
  reportRunWarning("Bad NMEA Msg: " + reason + ": " + msg);
  Notify("IM300_BAD_NMEA", reason + ": " + msg);
  return(false);
}

//---------------------------------------------------------
// Procedure: reportWarningsEvents()
//      Note: Get the AppCast-consistent events, warnings and
//            retractions from the sock ninja for posting

void M300::reportWarningsEvents()
{
  // Part 1: Handle Event Messages()
  list<string> events = m_ninja.getEvents();
  list<string>::iterator p;  
  for(p=events.begin(); p!=events.end(); p++) {
    string event_str = *p;
    reportEvent(event_str);
  }

  // Part 2: Handle Warning Messages()
  list<string> warnings = m_ninja.getWarnings();
  list<string> thrust_warnings = m_thrust.getWarnings();
  warnings.splice(warnings.end(), thrust_warnings);
  for(p=warnings.begin(); p!=warnings.end(); p++) {
    string warning_str = *p;
    reportRunWarning(warning_str);
  }

  // Part 3: Handle Retraction Messages()
  list<string> retractions = m_ninja.getRetractions();
  for(p=retractions.begin(); p!=retractions.end(); p++) {
    string retraction_str = *p;
    retractRunWarning(retraction_str);
  }
}
  
//------------------------------------------------------------
// Procedure: buildReport()
//
// -------------------------------------------
// Config:   max_r/t: 30/100      stale_check:  false
//           dr_mode: normal      stale_thresh: 15
// -------------------------------------------
// Drive     des_rud: -30         des_thrust_L: 0
// State:    des_thr: 40          des_thrust_R: 0
// -------------------------------------------
// Nav:      nav_x: 5968          nav_hdg: 0
//           nav_y: -6616.3       nav_spd: 0.5
// -------------------------------------------
// System:   voltage: 15.2        satellites: 0
// -------------------------------------------
// Comms:    Type: client         IPv4: 127.0.0.1 (of server)
//           Format: nmea         Port: 29500
//           Status: connected
// ---------------------------
// NMEA sentences:
// <--R     230  $CPNVG,105707.24,0000.00,N,00000.00,W,1,,,0,,,105707.24*64
// <--R     230  $CPRBS,105707.24,1,15.2,15.1,15.3,0*67
// <--R     230  $GPRMC,105707.24,A,0000.00,N,00000.00,W,1.1663,0,291263,0,E*76
//  S-->    231  $PYDIR,0,0*56


 
bool M300::buildReport() 
{
  string str_max_rud  = doubleToStringX(m_max_rudder,1);
  string str_max_thr  = doubleToStringX(m_max_thrust,1);
  string str_max_both = str_max_rud + "/" + str_max_thr;
  string str_des_rud  = doubleToStringX(m_thrust.getRudder(),1);
  string str_des_thr  = doubleToStringX(m_thrust.getThrust(),1);
  string str_des_thrL = doubleToStringX(m_thrust.getThrustLeft(),1);
  string str_des_thrR = doubleToStringX(m_thrust.getThrustRight(),1);
  string str_rot_hdg_tgt = doubleToStringX(m_rot_ctrl.getHeadingTarget(), 1);

  Notify("M4_DEBUG", str_des_thr);
  
  string str_sta_thr  = doubleToStringX(m_stale_threshold,1);
  string str_sta_ena  = boolToString(m_stale_check_enabled);

  string str_nav_x   = doubleToStringX(m_nav_x,1);
  string str_nav_y   = doubleToStringX(m_nav_y,1);
  string str_nav_hdg = doubleToStringX(m_nav_hdg,1);
  string str_nav_spd = doubleToStringX(m_nav_spd,1);
  string str_voltage = doubleToStringX(m_batt_voltage,1);
  string str_sats    = uintToString(m_num_satellites);


  string pd_ruth = padString(str_max_both, 10, false);
  string pd_drmo = padString(m_drive_mode, 10, false);
  string pd_drud = padString(str_des_rud, 10, false);
  string pd_dthr = padString(str_des_thr, 10, false);
  string pd_navx = padString(str_nav_x, 10, false);
  string pd_navy = padString(str_nav_y, 10, false);
  string pd_volt = padString(str_voltage, 10, false);

  
  m_msgs << "Config:    max_r/t: " << pd_ruth << "   stale_check:  " << str_sta_ena << endl;
  m_msgs << "           dr_mode: " << pd_drmo << "   stale_thresh: " << str_sta_thr << endl;
  m_msgs << "------------------------------------------------------" << endl;
  m_msgs << "Drive:     des_rud: " << pd_drud << "   des_thrust_L: " << str_des_thrL << endl;
  m_msgs << "State:     des_thr: " << pd_dthr << "   des_thrust_R: " << str_des_thrR << endl;
  m_msgs << "------------------------------------------------------" << endl;
  m_msgs << "Nav:       nav_x:   " << pd_navx << "   nav_hdg: " << str_nav_hdg << endl;
  m_msgs << "           nav_y:   " << pd_navy << "   nav_spd: " << str_nav_spd << endl;
  m_msgs << "------------------------------------------------------" << endl;
  m_msgs << "System:    voltage: " << pd_volt << "   satellites: " << str_sats << endl;
  m_msgs << "------------------------------------------------------" << endl;
  
  if ( m_rot_ctrl.getRotateInPlace() ) {
    m_msgs << "Rotation target heading: " << str_rot_hdg_tgt << endl;
    if ( m_rot_ctrl.checkClearToRotate( m_nav_x, m_nav_y, m_curr_time ) )
      m_msgs << "All clear to rotate.                                " << endl;
    m_msgs << "------------------------------------------------------" << endl;
  }

  cout << "Thrust: " << str_des_thrL << str_des_thrR << endl;

  if (m_add_thruster_fault){
    m_msgs << "Simulated Thruster Fault: ON                         " << endl;
    string str_fault_factor_thr_L   = doubleToStringX(m_fault_factor_thr_L,2);
    string str_fault_factor_thr_R   = doubleToStringX(m_fault_factor_thr_R,2);
    string str_fault_bias_thr_L     = doubleToStringX(m_fault_bias_thr_L,2);
    string str_fault_bias_thr_R     = doubleToStringX(m_fault_bias_thr_R,2);
    string str_fault_factor_rudder  = doubleToStringX(m_fault_factor_rudder, 2);
    string str_total_bias_thr_L     = doubleToStringX(m_rudder_bias_L + m_fault_bias_thr_L,2);
    string str_total_bias_thr_R     = doubleToStringX(m_rudder_bias_R + m_fault_bias_thr_R,2); 
    
    string pd_fault_factor_thr_L    = padString(str_fault_factor_thr_L, 10, false);
    string pd_fault_factor_thr_R    = padString(str_fault_factor_thr_R, 10, false);
    string pd_fault_bias_thr_L      = padString(str_fault_bias_thr_L, 10, false);
    string pd_fault_bias_thr_R      = padString(str_fault_bias_thr_R, 10, false);
    string pd_fault_factor_rudder   = padString(str_fault_factor_rudder, 10, false);
    string pd_total_bias_thr_L      = padString(str_total_bias_thr_L, 10, false);
    string pd_total_bias_thr_R      = padString(str_total_bias_thr_R, 10, false);
    
 
    m_msgs << "Fault factors: L = " << pd_fault_factor_thr_L << "   R = " << pd_fault_factor_thr_R << endl;
    m_msgs << "Fault biases : L = " << pd_fault_bias_thr_L << "   R = " << pd_fault_bias_thr_R << endl;
    m_msgs << "Fault rudder : G = " << pd_fault_factor_rudder << endl;
    m_msgs << "______________________________________________________" << endl;
    m_msgs << "Total biases : L = " << pd_total_bias_thr_L << "   R = " << pd_total_bias_thr_R << endl;
    
    
    m_msgs << "------------------------------------------------------" << endl;
  }
  list<string> summary_lines = m_ninja.getSummary();
  list<string>::iterator p;
  for(p=summary_lines.begin(); p!=summary_lines.end(); p++) {
    string line = *p;
    m_msgs << line << endl;
  }

  return(true);
}




