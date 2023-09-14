#!/bin/bash

mkdir results/results_rf/

while read RUN;
do
  echo $RUN

  ccdb dump /PHOTON_BEAM/hodoscope/fadc_time_offsets:${RUN} > adc_time_offsets.txt
  ccdb dump /PHOTON_BEAM/hodoscope/tdc_time_offsets:${RUN} > tdc_time_offsets.txt

  root -b -l -q slice_tagh.C\(${RUN}\)

  rm adc_time_offsets.txt tdc_time_offsets.txt

  ccdb add PHOTON_BEAM/hodoscope/tdc_time_offsets -r ${RUN}-${RUN} -v default results/results_rf/tdc_time_offsets_calib_${RUN}.txt
  ccdb add PHOTON_BEAM/hodoscope/fadc_time_offsets -r ${RUN}-${RUN} -v default results/results_rf/adc_time_offsets_calib_${RUN}.txt
done < runs_calib.dat

rm -r results/results_rf/