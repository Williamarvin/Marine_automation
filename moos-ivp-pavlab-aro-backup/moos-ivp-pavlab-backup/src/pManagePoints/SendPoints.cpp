/************************************************************/
/*    NAME: Mikala Molina                                    */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: SendPoints.cpp                     */
/*    DATE: June 1 2023                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "SendPoints.h"
#include "XYFormatUtilsPoint.h"
#include "GeomUtils.h"

using namespace std;

//---------------------------------------------------------
// Constructor()

SendPoints::SendPoints()
{
  m_need_to_send = false;
  m_min_dist =10; 
  m_all_initial_points_sent = false;
  m_minimum_points = 1; 
}

//---------------------------------------------------------
// Destructor

SendPoints::~SendPoints()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail()

bool SendPoints::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    string sval  = msg.GetString();
    string comm  = msg.GetCommunity();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

    if(key == "NODE_REPORT"){
      cout << "Node Report Received: " << sval << endl;
      NodeReport report = stringToNodeReport(sval);
      string vname = report.getName();
      for (int i=0; i<m_number_of_vehicles; i++){
        if(tolower(vname) == m_vehicle_names[i]){
          m_nav_xy_points[m_vehicle_names[i]].push_back(report.getXYPoint());
        }
      }
      //set m_vehicle_awake to true if the vehicle has sent a node report
      for (int i=0; i<m_number_of_vehicles; i++){
        if(tolower(vname) == m_vehicle_names[i]){
          m_vehicle_awake[m_vehicle_names[i]] = true;
        }
      }
     }

     else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer()

bool SendPoints::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool SendPoints::Iterate()
{
  AppCastingMOOSApp::Iterate();

//Check if a vehicle is awake. If it is, generate m_initial points number of initial points and create an XYSeglist of those points
  for (int i = 0; i < m_number_of_vehicles; i++){
    string vname = m_vehicle_names[i];
    if(m_vehicle_awake[vname] == true && m_needs_initial_points[vname] == true){
      for(int j = 0; j < m_initial_points; j++){
        XYPoint point = generateNewPoint();
        VisitPoint vpoint; 
        vpoint.initXY(point);
        vpoint.setID(intToString(m_id_counter[vname]));
        m_visit_points[vname].push_back(vpoint);
        m_id_counter[vname]++;
      }
      for(unsigned int j = 0; j < m_visit_points[vname].size(); j++){
        m_visit_point_seglists[vname].add_vertex(m_visit_points[vname][j].getX(), m_visit_points[vname][j].getY());
      }
      Notify("SURVEY_UPDATE_" +toupper(vname), "points=" + m_visit_point_seglists[vname].get_spec());
      m_needs_initial_points[vname] = false;
    }
  }
//if all vehicles have received their initial points, set m_all_initial_points_sent to true
  bool all_initial_points_sent = true;
  for (int i = 0; i < m_number_of_vehicles; i++){
    string vname = m_vehicle_names[i];
    if(m_needs_initial_points[vname] == true){
      all_initial_points_sent = false;
      break;
    }
  }
  if(all_initial_points_sent == true){
    m_all_initial_points_sent = true;
  }

//once all inital points are sent, start checking for visited points
  if(m_all_initial_points_sent == true){
    for (int i = 0; i < m_number_of_vehicles; i++){
      string vname = m_vehicle_names[i];
      for(unsigned int j = 0; j < m_visit_points[vname].size(); j++){
          bool checked = checkVisited(m_visit_points[vname][j], vname);
          if(checked == true){
            m_visit_points[vname][j].setState("visited");
            XYSegList unvisited_seglist;
            for(unsigned int k = 0; k < m_visit_points[vname].size(); k++){
              if(m_visit_points[vname][k].getState() == "unvisited"){
                unvisited_seglist.add_vertex(m_visit_points[vname][k].getX(), m_visit_points[vname][k].getY());
              }
            }
            Notify("SURVEY_UPDATE_" +toupper(vname), "points=" + unvisited_seglist.get_spec());
          }
        }
      }
    }
  
  //count the number of unvisited points for each vehicle
    for (int i = 0; i < m_number_of_vehicles; i++){
      string vname = m_vehicle_names[i];
      m_unvisited_count[vname] = countUnvisited(vname);
    }

    //count the number of visited points for each vehicle
    for (int i = 0; i < m_number_of_vehicles; i++){
      string vname = m_vehicle_names[i];
      int count = 0; 
      for(unsigned int j = 0; j < m_visit_points[vname].size(); j++){
        if(m_visit_points[vname][j].getState() == "visited"){
          count++;
        }
        m_visited_count[vname] = count;
      }
    }
  
  //if the number of unvisited points is less than m_minimum_points, generate a new point and add it to the seglist
    for (int i = 0; i < m_number_of_vehicles; i++){
      string vname = m_vehicle_names[i];
      if(m_unvisited_count[vname] < m_minimum_points){
        XYPoint point = generateNewPoint();
        VisitPoint vpoint; 
        vpoint.initXY(point);
        vpoint.setID(intToString(m_id_counter[vname]));
        m_visit_points[vname].push_back(vpoint);
        m_id_counter[vname]++;
        XYSegList unvisited_seglist;
        for(unsigned int j = 0; j < m_visit_points[vname].size(); j++){
          if(m_visit_points[vname][j].getState() == "unvisited"){
            unvisited_seglist.add_vertex(m_visit_points[vname][j].getX(), m_visit_points[vname][j].getY());
          }
        }
        Notify("SURVEY_UPDATE_" +toupper(vname), "points=" + unvisited_seglist.get_spec());
      }
    }

  AppCastingMOOSApp::PostReport();
  return(true);
}


//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool SendPoints::OnStartUp()
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
    if(param == "vnames") {
      m_vehicle_names = parseString(value, ',');
      m_number_of_vehicles = m_vehicle_names.size();
      for (int i = 0; i < m_number_of_vehicles; i++){
        m_vehicle_awake[m_vehicle_names[i]] = false;
        m_id_counter[m_vehicle_names[i]] = 0;
        m_needs_initial_points[m_vehicle_names[i]] = true;
      }
      handled = true;
    }
    else if(param == "initial_points") {
      m_initial_points = stoi(value);
      handled = true;
      cout << "Initial Points from parameters: " << m_initial_points << endl;
    }
    else if(param == "minimum_points") {
      m_minimum_points = stoi(value);
      handled = true;
      cout << "Minimum Points from parameters: " << m_minimum_points << endl;
    }
    else if(param == "capture_radius") {
      m_capture_radius = stoi(value);
      handled = true;
      cout << "Capture Radius from parameters: " << m_capture_radius << endl;
    }
    else if(param == "min_distance"){
      m_min_dist = stoi(value);
      handled = true; 
      cout << "minimum distance enforced between points (default 10): " << m_min_dist << endl; 
    }
    else if(param == "region") {
      m_region = value;
      if(m_region == "mit"){
        // m_region_poly.add_vertex(-13, -28);
        // m_region_poly.add_vertex(38, -5);
        // m_region_poly.add_vertex(53, -41);
        // m_region_poly.add_vertex(-3, -63);
        m_region_poly.add_vertex(60,10);
        m_region_poly.add_vertex(-30.3602,-32.8374);
        m_region_poly.add_vertex(-4.6578,-87.0535);
        m_region_poly.add_vertex(85.7024,-44.2161); 
        m_region_fld.addPolygon(m_region_poly);
      }
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

void SendPoints::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("NODE_REPORT", 0); 
}


//------------------------------------------------------------
// Procedure: buildReport()

bool SendPoints::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "File: SendPoints.cpp " << endl;
  m_msgs << "============================================" << endl;
 //generate a table of the vehicle names, if they are awake, if they need initial points, and how many points they have received
  ACTable actab(6);
  actab << "Vehicle" << "Awake" << "Needs Initial" << "Points Received" << "Unvisited Points" << "Visited Points";
  for (int i = 0; i < m_number_of_vehicles; i++){
    string vname = m_vehicle_names[i];
    actab << vname << boolToString(m_vehicle_awake[vname]) << boolToString(m_needs_initial_points[vname]) << intToString(m_id_counter[vname]) << intToString(m_unvisited_count[vname]) << intToString(m_visited_count[vname]);
  }
  m_msgs << actab.getFormattedString() << endl;

  m_msgs << "============================================" << endl;
  m_msgs << "Capture Radius: " << m_capture_radius << endl;
  m_msgs << "============================================" << endl;
  m_msgs << "Minimum points per vehicle: " << m_minimum_points << endl;
  m_msgs << "============================================" << endl;
  m_msgs << "All Intial points received? " << boolToString(m_all_initial_points_sent) << endl;


   

  return(true);
}
//-----------------------------------------------------------------
//Procedure: generateNewPoint()
//generates a new point within the region and ensures the point is atleast m_minimum_distance away from all unvisted points
XYPoint SendPoints::generateNewPoint()
{
  XYPoint point = m_region_fld.generatePoint();
  bool good_point = false; 
  while(!good_point){
    good_point = true;
    for(int i = 0; i < m_number_of_vehicles; i++){
      string vname = m_vehicle_names[i];
      for(unsigned int j = 0; j < m_visit_points[vname].size(); j++){
        double dist = distPointToPoint(point.get_vx(), point.get_vy(), m_visit_points[vname][j].getX(), m_visit_points[vname][j].getY());
        if(dist < m_min_dist){
          good_point = false; 
          point = m_region_fld.generatePoint();
          break;
        }
      }
    }
  }
  return point; 
}
//-----------------------------------------------------------------
//Procedure: checkVisited(XYPoint point)
//checks if a point is within m_capture_radius of a vehicles m_nav_xy_points vector
bool SendPoints::checkVisited(VisitPoint point, string vname)
{
  bool visited = false; 
  for(unsigned int i = 0; i < m_nav_xy_points[vname].size(); i++){
    double dist = distPointToPoint(point.getX(), point.getY(), m_nav_xy_points[vname][i].get_vx(), m_nav_xy_points[vname][i].get_vy());
    if(dist < m_capture_radius){
      visited = true; 
      point.setState("visited");
      //break;
    }
  }
  return visited; 
}
//-----------------------------------------------------------------
//Procedure: countUnvisited(string vname)
//counts the number of unvisited points for a vehicle
int SendPoints::countUnvisited(string vname)
{
  int count = 0; 
  for(unsigned int i = 0; i < m_visit_points[vname].size(); i++){
    if(m_visit_points[vname][i].getState() == "unvisited"){
      count++;
    }
  }
  return count; 
}
