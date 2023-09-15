# Script to streamline the calibration verification

#!/bin/bash

source env.sh

while read RUN;
do
    if [ ${RUN:0:1} != '#' ]
    then
        echo ${RUN}
    
        # Produce plots and statistics to verify the calibration
        root -b -l -q plot.C\(${RUN}\)
    fi
done < runs_calib.dat