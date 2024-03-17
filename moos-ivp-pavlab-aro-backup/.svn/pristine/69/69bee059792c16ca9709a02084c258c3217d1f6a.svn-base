#! /bin/bash

echo "Starting to parse all alog files. "
DATA_DIR="data"
mkdir -p $DATA_DIR

for dir in */; do

    case $dir in

	LOG_A*)
	    echo "Found abe"
	    aloggrep OWN_OPINION_STATE --tv -f -csc -sd LOG_A*/*.alog $DATA_DIR/abe_opinions.alog
	    aloggrep OWN_ATTENTION --tv -f -csc -sd LOG_A*/*.alog $DATA_DIR/abe_attention.alog
	    ;;
	LOG_B*)
	    echo "Found ben"
	    aloggrep OWN_OPINION_STATE --tv -f -csc -sd LOG_B*/*.alog $DATA_DIR/ben_opinions.alog
	    aloggrep OWN_ATTENTION --tv -f -csc -sd LOG_B*/*.alog $DATA_DIR/ben_attention.alog
	    ;;
	LOG_C*)
	    echo "Found cal"
	    aloggrep OWN_OPINION_STATE --tv -f -csc -sd LOG_C*/*.alog $DATA_DIR/cal_opinions.alog
	    aloggrep OWN_ATTENTION --tv -f -csc -sd LOG_C*/*.alog $DATA_DIR/cal_attention.alog
	    ;;
	LOG_D*)
	    echo "Found deb"
	    aloggrep OWN_OPINION_STATE --tv -f -csc -sd LOG_D*/*.alog $DATA_DIR/deb_opinions.alog
	    aloggrep OWN_ATTENTION --tv -f -csc -sd LOG_D*/*.alog $DATA_DIR/deb_attention.alog
	    ;;
	LOG_E*)
	    echo "Found eve"
	    aloggrep OWN_OPINION_STATE --tv -f -csc -sd LOG_E*/*.alog $DATA_DIR/eve_opinions.alog
	    aloggrep OWN_ATTENTION --tv -f -csc -sd LOG_E*/*.alog $DATA_DIR/eve_attention.alog
	    ;;
	LOG_F*)
	    echo "Found fin"
	    aloggrep OWN_OPINION_STATE --tv -f -csc -sd LOG_F*/*.alog $DATA_DIR/fin_opinions.alog
	    aloggrep OWN_ATTENTION --tv -f -csc -sd LOG_F*/*.alog $DATA_DIR/fin_attention.alog
	    ;;
	LOG_G*)
	    echo "Found gil"
	    aloggrep OWN_OPINION_STATE --tv -f -csc -sd LOG_G*/*.alog $DATA_DIR/gil_opinions.alog
	    aloggrep OWN_ATTENTION --tv -f -csc -sd LOG_G*/*.alog $DATA_DIR/gil_attention.alog
	    ;;
	LOG_H*)
	    echo "Found hix"
	    aloggrep OWN_OPINION_STATE --tv -f -csc -sd LOG_H*/*.alog $DATA_DIR/hix_opinions.alog
	    aloggrep OWN_ATTENTION --tv -f -csc -sd LOG_H*/*.alog $DATA_DIR/hix_attention.alog
	    ;;
	*)
	    echo "Found other directory, skipping"
	    ;;
    esac
done


# Plot these values?
while true; do
    read -p "Do you want to produce an opinion plot for this run? [y/n] " yn
    case $yn in
	[Yy]* ) ~/moos-ivp-pavlab/scripts/opinion_analysis/plot_data.py; break;;
	[Nn]* ) break;;
	* ) echo "Please answer yes or no.";;
    esac
done

# make animations?
while true; do
    read -p "Do you want to generate an animation for all vehicles? [y/n] " yn
    case $yn in
	[Yy]* ) ~/moos-ivp-pavlab/scripts/opinion_analysis/animate_data.py; break;;
	[Nn]* ) break;;
	* ) echo "Please answer yes or no.";;
    esac
done


