/************************************************************/
/*    NAME: Tyler Paine                                     */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: TrajectTranslate.h                              */
/*    DATE: March 14th, 2023                                */
/************************************************************/

#ifndef TrajectTranslate_HEADER
#define TrajectTranslate_HEADER

#include <string>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"


class TrajectTranslate : public AppCastingMOOSApp
{
 public:
   TrajectTranslate();
   ~TrajectTranslate();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();
   bool checkReadyToGo();

 protected:
   void registerVariables();

 private: // Configuration variables

   std::string m_body_heading_var; 
   double m_time_const_vel_x;  // Hz
   double m_time_const_vel_y;
   double m_time_const_ang_z;
   
   
   double m_time_window;  // inputs must be within this window
                          // of each other.

   double m_heading_rate_scale; // linear coefficient

 private: // State variables
   double m_desired_heading;
   double m_desired_speed;
   double m_compass_heading_raw;

   double m_desired_heading_time;
   double m_desired_speed_time;
   double m_compass_heading_raw_time;

   double m_last_publish_time;

   bool  m_got_desired_heading;
   bool  m_got_desired_speed;
   bool  m_got_compass_heading_raw;
   bool  m_deploy;
   bool  m_des_speed_in_surge_only; 

   // Output state filtering
   double m_des_traject_vel_x_last;
   double m_des_traject_vel_y_last;
   double m_des_traject_ang_z_last;

};

#endif 
