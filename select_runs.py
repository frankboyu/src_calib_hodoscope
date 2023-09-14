import rcdb
import sys

db = rcdb.RCDBProvider("mysql://rcdb@hallddb/rcdb")

file = open("runs_all.txt", "w")

good_runs = db.select_runs("@is_cpp_production and status!=0", 100001, 109999)
for run in good_runs:
    file.write(str(run)[-8:-2]+"\n")
    
good_runs = db.select_runs("@is_primex_production and status!=0", 110001, 119999)
for run in good_runs:
    file.write(str(run)[-8:-2]+"\n")
    
good_runs = db.select_runs("@is_dirc_production and status!=0", 120001, 129999)
for run in good_runs:
    file.write(str(run)[-8:-2]+"\n")
