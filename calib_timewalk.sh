# Script to streamline the calibrations of the time-walk corrections

#!/bin/bash

source env.sh

while read RUN;
do
    if [ ${RUN:0:1} != '#' ]
    then
        echo ${RUN}
    
        # Make a temporary directory to put the fit results
        mkdir gaussian-fits-csv

        # Produce the time-walk calibration constants
        root -b -l -q gaussian_fits.C\(${RUN}\)
        root -b -l -q timewalk_fits.C\(${RUN}\)

        # Upload the calibration constants to the CCDB
        ccdb add PHOTON_BEAM/hodoscope/tdc_timewalk -r ${RUN}-${RUN} -v default tw-corr-new.txt

        # Delete the intermediate files
        rm -r gaussian-fits-csv 
        rm timewalk-fits.txt tw-corr-new.txt
    fi
done < runs_calib.dat