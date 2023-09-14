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