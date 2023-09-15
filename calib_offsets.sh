# Script to streamline the calibrations of the timing offsets

#!/bin/bash

source env.sh

while read RUN;
do
    if [ ${RUN:0:1} != '#' ]
    then
        echo ${RUN}
    
        # Download the current calibration constants from the CCDB
        ccdb dump /PHOTON_BEAM/hodoscope/base_time_offset:${RUN} > base-time-offsets-ccdb.txt
        ccdb dump /PHOTON_BEAM/hodoscope/tdc_time_offsets:${RUN} > tdc-time-offsets-ccdb.txt
        ccdb dump /PHOTON_BEAM/hodoscope/fadc_time_offsets:${RUN} > adc-time-offsets-ccdb.txt

        # Produce the updated calibration constants
        root -b -q fits.C\(${RUN}\)
        root -b -q offsets.C\(${RUN}\)

        # Upload the calibration constants to the CCDB
        ccdb add /PHOTON_BEAM/hodoscope/base_time_offset -v default -r ${RUN}-${RUN} base-time-offsets-new.txt '#Fix some outlier channels'
        ccdb add /PHOTON_BEAM/hodoscope/tdc_time_offsets -v default -r ${RUN}-${RUN} tdc-time-offsets-new.txt '#Fix some outlier channels'
        ccdb add /PHOTON_BEAM/hodoscope/fadc_time_offsets -v default -r ${RUN}-${RUN} adc-time-offsets-new.txt '#Fix some outlier channels'

        # Delete the intermediate files
        rm results_TAGH.txt results_TDCADC.txt
        rm base-time-offsets-ccdb.txt tdc-time-offsets-ccdb.txt adc-time-offsets-ccdb.txt
        rm base-time-offsets-new.txt  tdc-time-offsets-new.txt  adc-time-offsets-new.txt
    fi
done < runs_calib.dat