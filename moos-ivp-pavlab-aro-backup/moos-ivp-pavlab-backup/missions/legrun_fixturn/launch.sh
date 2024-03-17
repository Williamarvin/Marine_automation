#!/bin/bash
#---------------------------------------------------------------
#   Script: launch.sh
#  Mission: legrun_fixturn
#   Author: Mike Benjamin
#   LastEd: Nov 2023
#-------------------------------------------------------------- 
#  Part 1: Define a convenience function for producing terminal
#          debugging/status output depending on the verbosity.
#-------------------------------------------------------------- 
vecho() { if [ "$VERBOSE" != "" ]; then echo "$ME: $1"; fi }

#---------------------------------------------------------------
#  Part 2: Set global var defaults
#---------------------------------------------------------------
ME=`basename "$0"`
TIME_WARP=1
JUST_MAKE=""
VERBOSE=""
VNAME1="abe"
CLEAN="no"
CMD_ARGS=""

MAXSPD=""
RANDSTART="true"
MOD=""

VNAMES=""
VLAUNCH_ARGS=" --auto --sim --vname=$VNAME1 "
SLAUNCH_ARGS=" --auto --sim "

#---------------------------------------------------------------
#  Part 3: Check for and handle command-line arguments
#---------------------------------------------------------------
for ARGI; do
    CMD_ARGS+="${ARGI} "
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ]; then
	echo "$ME [OPTIONS] [time_warp]                      "
	echo "                                               "
	echo "Options:                                       "
	echo "  --help, -h                                   "
	echo "    Show this help message                     "
	echo "  --just_make, -j                              "
	echo "    Just make targ files, no launch            "
	echo "  --verbose, -v                                "
	echo "    Increase verbosity,  confirm before launch "
	echo "  --clean, -c                                  "
	echo "    Run clean.sh and ktm prior to launch       "
	echo "  --norand                                     " 
	echo "    Do not randomly generate vpositions.txt.   "
	echo "  --maxspd=<m/s>                               "
	echo "    Example: --maxspd=2                        "
	echo "  --mod=<mission>                              "
	echo "    Example: --mod=aturn                       "
	exit 0
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_make" -o "${ARGI}" = "-j" ]; then
	JUST_MAKE=$ARGI
    elif [ "${ARGI}" = "--verbose" -o "${ARGI}" = "-v" ]; then
	VERBOSE=$ARGI
    elif [ "${ARGI}" = "--clean" -o "${ARGI}" = "-cc" ]; then
	CLEAN="yes"
    elif [ "${ARGI:0:6}" = "--mod=" ]; then
        MOD=$ARGI
    elif [ "${ARGI:0:9}" = "--maxspd=" ]; then
        MAXSPD=$ARGI
    else
        echo "$ME: Bad arg:" $ARGI "Exit Code 1."
        exit 1
    fi
done

VLAUNCH_ARGS+=" $VERBOSE $JUST_MAKE $TIME_WARP "
SLAUNCH_ARGS+=" $VERBOSE $JUST_MAKE $TIME_WARP "

#---------------------------------------------------------------
#  Part 4: If verbose, show vars and confirm before launching
#---------------------------------------------------------------
if [ "${VERBOSE}" != "" ]; then 
    echo "======================================="
    echo "  launch.sh SUMMARY                    "
    echo "======================================="
    echo "$ME"
    echo "CMD_ARGS  = [${CMD_ARGS}]              "
    echo "TIME_WARP = [${TIME_WARP}]             "
    echo "JUST_MAKE = [${JUST_MAKE}]             "
    echo "---------------------------------------"
    echo "AUTO      = [${AUTO}]                  "
    echo "MOD       = [${MOD}]                   "
    echo "---------------------------------------"
    echo -n "Hit the RETURN key to continue with launching"
    read ANSWER
fi

#-------------------------------------------------------------
# Part 5A: If Cleaning enabled, clean first
#-------------------------------------------------------------
vecho "Running ./clean.sh and ktm prior to launch"
if [ "${CLEAN}" = "yes" ]; then
    ./clean.sh; ktm
fi

#-------------------------------------------------------------
# Part 5C: Launch the vehicle
#-------------------------------------------------------------
START="x=-17,y=-18,heading=140"
VNAMES+="abe"

VLAUNCH_ARGS+=" $NOCONFIRM $MOD $MAXSPD"
VLAUNCH_ARGS+=" --start=$START    "
VLAUNCH_ARGS+=" --mport=9001 "
VLAUNCH_ARGS+=" --pshare=9201 "
VLAUNCH_ARGS+=" --speed=$TRANSIT_SPD " 
VLAUNCH_ARGS+=" --color=green" 
VLAUNCH_ARGS+=" --shore=localhost "

./launch_vehicle.sh $VLAUNCH_ARGS	
if [ $? != 0 ]; then
    exit 1
fi

#---------------------------------------------------------------
#  Part 6: Launch the shoreside
#---------------------------------------------------------------
echo "$ME: Launching Shoreside ..."
./launch_shoreside.sh $SLAUNCH_ARGS --vnames=$VNAMES

#---------------------------------------------------------------
#  Part 7: If launched from script, we're done, exit now
#---------------------------------------------------------------
if [ "${AUTO_LAUNCHED}" = "yes" -o "${JUST_MAKE}" != "" ]; then
    exit 0
fi

#---------------------------------------------------------------
# Part 8: Launch uMAC until the mission is quit
#---------------------------------------------------------------
uMAC targ_shoreside.moos
kill -- -$$

