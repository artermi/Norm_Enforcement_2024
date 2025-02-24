import sys
import os
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
from scipy.ndimage import gaussian_filter1d
from matplotlib import rc


def remove_outliers_and_average(numbers, method="iqr", threshold=1.5):
    if not numbers:
        return None  # Handle empty list case

    numbers = np.array(numbers)

    if method == "iqr":
        # Use the interquartile range (IQR) method
        Q1, Q3 = np.percentile(numbers, [25, 75])
        IQR = Q3 - Q1
        lower_bound = Q1 - threshold * IQR
        upper_bound = Q3 + threshold * IQR

    elif method == "std":
        # Use the standard deviation method
        mean = np.mean(numbers)
        std_dev = np.std(numbers)
        lower_bound = mean - threshold * std_dev
        upper_bound = mean + threshold * std_dev

    else:
        raise ValueError("Invalid method. Choose 'iqr' or 'std'.")

    # Filter the numbers within bounds
    filtered_numbers = numbers[(numbers >= lower_bound) & (numbers <= upper_bound)]

    if len(filtered_numbers) == 0:
        return None  # Avoid division by zero if all numbers are outliers

    return np.mean(filtered_numbers)


D = []
C = []
SC = []
SC2 = []

AVG = []
b = []


d_name = '.'
t_name = 'new_b.tex'
if len(sys.argv) > 2:
    d_name = sys.argv[1]
    t_name = sys.argv[2]

for root,dirs,files in sorted(os.walk(d_name,topdown = False)):

    for name in sorted(files):
        if name.find('.dat') >= 0 and name.find('avg') < 0:
            # r_0200_b_0050_g_0020_mod_00.dat
            # 0123456789|123456789|1234567
            bb = float(name[9:13])/100

            Final_D = []
            Final_C = []
            FinalSC = []
            FinalSC2 = []
            with open(os.path.join(root, name)) as file:
                for last_line in file:
                    nmbs = last_line.split()
                    Final_D.append(float(nmbs[1]))
                    Final_C.append(float(nmbs[2]))
                    FinalSC.append(float(nmbs[3]))
                    FinalSC2.append(float(nmbs[4]))

#                   if int(nmbs[0]) == 10000:
#                       break


            b.append(bb)
            D.append(remove_outliers_and_average(Final_D))
            C.append( remove_outliers_and_average(Final_C) )
            SC.append( remove_outliers_and_average(FinalSC) ) 
            SC2.append( remove_outliers_and_average(FinalSC2) ) 
#            D.append( sum(Final_D[-100:])/100 )
#            C.append( sum(Final_C[-100:])/100 )
#            SC.append( sum(FinalSC[-100:])/100 ) 
#            SC2.append( sum(FinalSC2[-100:])/100 ) 

        if name.find('.dat') >= 0 and name.find('avg') > 0:
            with open(os.path.join(root, name)) as file:
                for last_line in file:
                    pass
            AVG.append(float(last_line))

PS = [100 for i in b]

ax = plt.subplot(111)
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * 0.8])
#ax.plot(itr, L, color='#cb4335', marker= '.', label = 'Fixed defector')

#D = gaussian_filter1d(D,.5)
#C = gaussian_filter1d(C,.5)
#SC = gaussian_filter1d(SC,.5)
#SC2 = gaussian_filter1d(SC2,.5)

ax.plot(b, D, color='red', marker= '.',label = 'D',markersize=2)
ax.plot(b, C, color='blue', marker= '.',label = 'C',markersize=2)
ax.plot(b, SC, color='green', marker= '.',label = r'$P_1$',markersize=2)
ax.plot(b, SC2, color='magenta', marker= '.',label = r'$P_2$',markersize=2)

#ax.plot(b, PS, color='magenta', marker= '.',label = 'Average',markersize=2)

ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.2), fancybox=True, shadow=True, ncol=4)


#ax2 = ax.twinx()
#ax2.plot(b,AVG,color='magenta', marker= '.',label = 'Average',markersize=2)

ax.set_ylim([-0.1,1.1])
#ax2.set_ylim([2.5,3])
ax.set_xlabel(r'$\beta$')
ax.set_ylabel('Fractions')
#ax2.set_ylabel('Earnings')

plt.grid(False)

import tikzplotlib

tikzplotlib.save(t_name)