# Script to check if the histogram files are in place and rename them
# For every run, the one output file is renamed to remove the evio file number so that the consistency is kept
# Then all the files are moved to the same folder for the convenience when browsing

#!/bin/bash

while read RUN;
do
    if   [ -e results/hists/${RUN}/hd_root_${RUN}_000.root ]
    then
        mv results/hists/${RUN}/hd_root_${RUN}_000.root results/hists/hd_root_${RUN}.root
        rm -r results/hists/${RUN}/
        continue
        
    elif [ -e results/hists/${RUN}/hd_root_${RUN}_001.root ]
    then
        mv results/hists/${RUN}/hd_root_${RUN}_001.root results/hists/hd_root_${RUN}.root
        rm -r results/hists/${RUN}/
        continue

    elif [ -e results/hists/${RUN}/hd_root_${RUN}_002.root ]
    then
        mv results/hists/${RUN}/hd_root_${RUN}_002.root results/hists/hd_root_${RUN}.root
        rm -r results/hists/${RUN}/
        continue

    else    
        echo "${RUN}: file not found"
    fi
done < runs_calib.dat