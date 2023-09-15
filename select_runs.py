# Script to get the list of production runs from RCDB

import rcdb
import sys

db = rcdb.RCDBProvider("mysql://rcdb@hallddb/rcdb")

file = open("runs_all.dat", "w")
file.write("#List of all the production runs in the run periods of interest\n")

# RunPeriod-2022-05, CPP/NPP
good_runs = db.select_runs("@is_cpp_production and status!=0", 100001, 109999)
for run in good_runs:
    file.write(str(run)[-8:-2]+"\n")
    
# RunPeriod-2022-08, PrimEx phase III    
good_runs = db.select_runs("@is_primex_production and status!=0", 110001, 119999)
for run in good_runs:
    file.write(str(run)[-8:-2]+"\n")

# RunPeriod-2023-01, GlueX II
good_runs = db.select_runs("@is_dirc_production and status!=0", 120001, 129999)
for run in good_runs:
    file.write(str(run)[-8:-2]+"\n")
