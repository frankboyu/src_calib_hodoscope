## src_calib_hodoscope

Scripts to calibrate the tagger hodoscope of the GlueX detector at Jefferson Lab Hall D for the SRC/CT experiment and beyond

JLab file system: /work/halld2/home/boyu/src_calib_hodoscope

GitHub: https://github.com/frankboyu/src_calib_hodoscope/tree/master

### Usage

1.  Compile a list of runs to be calibrated

    Edit runs_calib.dat to have the list of runs used in all following steps.
   
    Optional: to get a list of all production runs to the file runs_all.dat for the run periods of interest 
   
    `python select_runs.py`

2.  Run hd_root with the TAGH_timewalk plugin

    `sh files_submit.sh`
    
    A list of jobs will be submitted using swif2 to the farm and automatically run.
    
    After all the jobs are finished,
    
    `sh files_check.sh`
    
    It will check if all the files are in place and rename them for later convenience.
    
3.  Calibrate the timing offsets of each channel

    `sh calib_offsets.sh`
    
    Every channel will be aligned with the nearest RF bunch using Gaussian fits. Then the new constants will be published to CCDB.
    
4.  Repeat step 2

5.  Calibrate the time-walk correction

    `sh calib_timewalk.sh`
    
    Every channel will be corrected with the known time-walk function. Then the new constants will be published to CCDB.
    
6.  Repeat step 2

7.  Verify the calibration

    `sh calib_verify.sh`
    
    It will produce a statistics file to check quantitively and a plot file to check qualitiively for each run.
    
    To get a summarized version for all the runs, use summary.ipynb
    
    All the output files will be located at results/verify

### Notes

1. Original version of the code is located at: https://github.com/JeffersonLab/halld_recon/tree/master/src/plugins/Calibration/TAGH_timewalk

2. For the alignment with the correct RF bunch, refer to the HLDetectorTiming plugin: https://github.com/JeffersonLab/halld_recon/tree/master/src/plugins/Calibration/HLDetectorTiming