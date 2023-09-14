import numpy as np
import matplotlib.pyplot as plt

file = open('results/verify/summary_problems.txt','w')

numbers = np.zeros(3000)
offsets = np.zeros((3000,2,274))
resolutions = np.zeros((3000,2,274))
runlist = np.loadtxt("runs_calib.dat",dtype=int)
i = -1

for run in runlist:
    if np.loadtxt("results/verify/stats-"+str(run)+".txt").size>0:
        i += 1
        
        numbers[i] = run
        offsets[i,0,:] = np.loadtxt("results/verify/stats-"+str(run)+".txt")[:,1]*1000
        offsets[i,1,:] = np.loadtxt("results/verify/stats-"+str(run)+".txt")[:,5]*1000
        resolutions[i,0,:] = np.loadtxt("results/verify/stats-"+str(run)+".txt")[:,2]*1000
        resolutions[i,1,:] = np.loadtxt("results/verify/stats-"+str(run)+".txt")[:,6]*1000
        
        if np.average(abs(offsets[i,0,:])) > 500:
            file.write(str(run)+": average TDC-ADC offset is "+str("%.2f" % np.average(abs(offsets[i,0,:])))+" ps, greater than 500 ps\n")
            #file.write(str(run)+"\n")
            #continue
        if np.average(abs(offsets[i,1,:])) > 500:
            file.write(str(run)+": average TDC-RF offset is "+str("%.2f" % np.average(abs(offsets[i,1,:])))+" ps, greater than 500 ps\n")
            #file.write(str(run)+"\n")
            #continue 
        if np.max(abs(offsets[i,0,:])) > 1000:
            file.write(str(run)+": max TDC-ADC offset is "+str("%.2f" % np.max(abs(offsets[i,0,:])))+" ps, greater than 1000 ps\n")
            #file.write(str(run)+"\n")
            #continue
        if np.max(abs(offsets[i,1,:])) > 1000:
            file.write(str(run)+": max TDC-RF offset is "+str("%.2f" % np.max(abs(offsets[i,1,:])))+" ps, greater than 1000 ps\n")
            #file.write(str(run)+"\n")
            #continue
        #if np.average(resolutions[i,1,:]) > 200:
            #file.write(str(run)+" average TDC-RF resolution is "+str("%.2f" % np.average(abs(resolutions[i,1,:])))+" ps, greater than 200 ps\n")
            #file.write(str(run)+"\n")
            #continue
        #if np.average(resolutions[i,1,:]) < 100:
            #file.write(str(run)+" average TDC-RF resolution is "+str("%.2f" % np.average(abs(resolutions[i,1,:])))+" ps, smaller than 100 ps\n")
            #file.write(str(run)+"\n")
            #continue
    else:
        file.write(str(run)+" file doesn't exist\n")

plt.scatter(numbers[:i],np.average(abs(offsets[:i,0,:]),axis=1))
plt.ylim([0,200])
plt.xlabel("Run")
plt.ylabel("TDC-ADC offset(ps)")
plt.title("TDC-ADC offsets, average of all sectors")
plt.savefig('results/verify/summary_offsets_tdc-adc_average.png')
plt.close()

plt.scatter(numbers[:i],np.average(abs(offsets[:i,1,:]),axis=1))
plt.ylim([0,200])
plt.xlabel("Run")
plt.ylabel("TDC-RF offset(ps)")
plt.title("TDC-RF offsets, average of all sectors")
plt.savefig('results/verify/summary_offsets_tdc-rf_average.png')
plt.close()

plt.scatter(numbers[:i],np.average(resolutions[:i,1,:],axis=1))
plt.ylim([0,400])
plt.xlabel("Run")
plt.ylabel("TDC resolution(ps)")
plt.title("TDC resolutions, average of all sectors")
plt.savefig('results/verify/summary_resolutions_average.png')
plt.close()

