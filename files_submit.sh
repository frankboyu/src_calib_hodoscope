#!/bin/bash

source env.sh
python launch.py jobs_tagh_timewalk.cfg
swif2 run -workflow src_calib_hodoscope -maxconcurrent 1000
