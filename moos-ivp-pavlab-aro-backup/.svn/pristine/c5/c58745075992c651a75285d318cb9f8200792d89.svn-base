/****************************************************************/
/*   NAME: Tyler Paine                                          */
/*   ORGN: MIT, Cambridge MA                                    */
/*   FILE: TrajectTranslate_Info.cpp                            */
/*   DATE: March 14th, 2023                                     */
/****************************************************************/

#include <cstdlib>
#include <iostream>
#include "TrajectTranslate_Info.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("------------------------------------                            ");
  blk("  The pTrajectTranslate application is used for translating     ");
  blk("  the decisions from pHelmIvP into a smooth trajectory in       ");
  blk("  body-relative coordinates.  The decisions are transformed     ");
  blk("  into local (body-relative) coordinates, and then each output  ");
  blk("  is then filtered using a first-order filter. The time         ");
  blk("  constants used in the filter for each coordinate axis can be  ");
  blk("  configured.                                                   ");
  blk("                                                                ");
}

//----------------------------------------------------------------
// Procedure: showHelpAndExit

void showHelpAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("Usage: pTrajectTranslate file.moos [OPTIONS]                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("Options:                                                        ");
  mag("  --alias","=<ProcessName>                                      ");
  blk("      Launch pTrajectTranslate with the given process name         ");
  blk("      rather than pTrajectTranslate.                           ");
  mag("  --example, -e                                                 ");
  blk("      Display example MOOS configuration block.                 ");
  mag("  --help, -h                                                    ");
  blk("      Display this help message.                                ");
  mag("  --interface, -i                                               ");
  blk("      Display MOOS publications and subscriptions.              ");
  mag("  --version,-v                                                  ");
  blk("      Display the release version of pTrajectTranslate.        ");
  blk("                                                                ");
  blk("Note: If argv[2] does not otherwise match a known option,       ");
  blk("      then it will be interpreted as a run alias. This is       ");
  blk("      to support pAntler launching conventions.                 ");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showExampleConfigAndExit

void showExampleConfigAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("pTrajectTranslate Example MOOS Configuration                    ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = pTrajectTranslate                               ");
  blk("{                                                               ");
  blk("  AppTick   = 4                                                 ");
  blk("  CommsTick = 4                                                 ");
  blk("                                                                ");
  blu("   time_window = [0.5]                                          ");
  blk("                                                                ");
  blk("   // Heading rate scale is used to calculate                   ");
  blk("   // desired heading rate with the following                   ");
  blk("   // formulas:                                                 ");
  blk("   // delta_theta = desired_heading - compass_heading           ");
  blk("   // desired_heading_rate = heading_rate_scale * delta_theta   ");
  blk("   // (and the result is input to the lowpass filter)           ");
  blu("   heading_rate_scale = [0.1]                                   ");
  blk("                                                                ");
  blu("   cutoff_freq_vel_x = [20]  // Hz                              ");
  blu("   cutoff_freq_vel_y = [20]  // Hz                              ");
  blu("   cutoff_freq_ang_z = [20]  // Hz                              ");
  blk("                                                                ");
  blk("   // Variable for the compass heading                          ");
  blu("   body_heading_var = [COMPASS_HEADING_RAW]                     ");
  blk("                                                                ");
  blk("   // Configuration for translation of desired speed into       ");
  blk("   // body-relative x and y velocity:                           ");
  blu("   des_speed_in_surge_only = true or [false]                    ");
  blk("           true -> vel_x = DESIRED_SPEED                        ");
  blk("          false -> DESIRED_SPEED is projected into body-relative");
  blk("                   coordinates                                  ");
  blk("}                                                               ");
  blk("                                                                ");
  exit(0);
}


//----------------------------------------------------------------
// Procedure: showInterfaceAndExit

void showInterfaceAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("pTrajectTranslate INTERFACE                                     ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("SUBSCRIPTIONS:                                                  ");
  blk("------------------------------------                            ");
  blk("  NODE_MESSAGE = src_node=alpha,dest_node=bravo,var_name=FOO,   ");
  blk("                 string_val=BAR                                 ");
  blk("                                                                ");
  blu("  DESIRED_HEADING = From pHelmIvP                               ");
  blk("                                                                ");
  blu("  DESIRED_SPEED   = From pHelmIvP                               ");
  blk("                                                                ");
  blu("  COMPASS_HEADING_RAW  = Deg north from imu (iM300)             ");
  blk("                                                                ");
  blk("PUBLICATIONS:                                                   ");
  blk("------------------------------------                            ");
  blk("  Smooth trajectory as a twist in body-relative                 ");
  blk("  North East Down (NED) (XYZ) coordinates:                      ");
  blk("  (+X is forward, +Y is starboard, +Z is clockwise)             ");
  blk("                                                                ");
  blu("  DESIRED_VEL_TWIST_LINEAR_X   (double)                         ");
  blu("  DESIRED_VEL_TWIST_LINEAR_Y   (double)                         ");
  blu("  DESIRED_VEL_TWIST_ANGULAR_Z  (double)                         ");
  blk("                                                                ");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("pTrajectTranslate", "gpl");
  exit(0);
}

