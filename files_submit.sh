# Script to submit the jobs to the farm for running hd_root with the TAGH_timewalk plugin

#!/bin/bash

source env.sh

# Remove all previous files to have a clean slate
rm results/hists/*

# Submit the jobs and run the workflow
python launch.py jobs_tagh_timewalk.cfg
swif2 run -workflow src_calib_hodoscope -maxconcurrent 1000
