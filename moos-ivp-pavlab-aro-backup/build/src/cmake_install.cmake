# Install script for directory: /home/orangepi/Documents/moos-ivp-pavlab-aro/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "None")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/KayakEvalEngineUtils/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pManagePoints/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pGenGreedyRescue/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uFldCollisionDetectColregs/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_sock_utils/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_eval_engine/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_serialdev/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_seatrac_tools/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_convoy/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_colregsV22/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_anderson/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_pmview/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_navcheck/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_legrunz/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_legrun/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_convoy/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/iM300/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/iM300X/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/app_survey_plan/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pTestPost/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/iM300Health/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pEvalConvoy/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pGeoSelect/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pTrajectTranslate/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pFalconRunMgr/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_bhv_shell/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/iHydroLinkArduinoBridge/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/iSeaTracX150V0/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_SearchBHV/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_VectorBHV/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_opinion/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionManager/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionInput/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pOpinionFixer/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/iSerial/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uFldBloomStormSim/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/lib_MoveToRegion/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/pBloomStormCtrl/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/app_test_armadillo/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSimHeron/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uSockComms/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/app_alogceval/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/app_convoy_order/cmake_install.cmake")
  include("/home/orangepi/Documents/moos-ivp-pavlab-aro/build/src/uFldConvoyEval/cmake_install.cmake")

endif()

