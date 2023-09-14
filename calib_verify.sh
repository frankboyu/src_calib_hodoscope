#!/bin/bash

while read RUN;
do
  echo $RUN
  root -b -l -q plot.C\(${RUN}\)
done < runs_calib.dat