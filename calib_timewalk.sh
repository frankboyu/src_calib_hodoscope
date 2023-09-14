#!/bin/bash

while read RUN;
do
  echo $RUN
  
  mkdir gaussian-fits-csv
  
  root -b -l -q gaussian_fits.C\(${RUN}\)
  root -b -l -q timewalk_fits.C\(${RUN}\)

  ccdb add PHOTON_BEAM/hodoscope/tdc_timewalk -r ${RUN}-${RUN} -v default tw-corr-new.txt
  
  rm -r gaussian-fits-csv 
  rm timewalk-fits.txt tw-corr-new.txt
done < runs_calib.dat