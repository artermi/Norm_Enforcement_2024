import sys
import os
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
from scipy.ndimage import gaussian_filter1d
from matplotlib import rc
import tikzplotlib


def remove_outliers(numbers, method="iqr", threshold=1.5):
    if not numbers:
        return []

    numbers = np.array(numbers)

    if method == "iqr":
        Q1, Q3 = np.percentile(numbers, [25, 75])
        IQR = Q3 - Q1
        lower_bound = Q1 - threshold * IQR
        upper_bound = Q3 + threshold * IQR

    elif method == "std":
        mean = np.mean(numbers)
        std_dev = np.std(numbers)
        lower_bound = mean - threshold * std_dev
        upper_bound = mean + threshold * std_dev

    else:
        raise ValueError("Invalid method. Choose 'iqr' or 'std'.")

    return numbers[(numbers >= lower_bound) & (numbers <= upper_bound)]


def mean_and_error(numbers):
    if len(numbers) == 0:
        return None, None
    mean = np.mean(numbers)
    error = np.std(numbers)
    return mean, error


D, C, SC, SC2 = [], [], [], []
D_err, C_err, SC_err, SC2_err = [], [], [], []
b = []

d_name = '.'
t_name = 'new_b.tex'
if len(sys.argv) > 2:
    d_name = sys.argv[1]
    t_name = sys.argv[2]

for root, dirs, files in os.walk(d_name, topdown=True):
    for name in sorted(files):
        if name.endswith('.dat') and 'avg' not in name:
            bb = float(name.split('_')[3]) / 1000

            Final_D, Final_C, FinalSC, FinalSC2 = [], [], [], []
            with open(os.path.join(root, name)) as file:
                for line in file:
                    nmbs = line.split()
                    Final_D.append(float(nmbs[1]))
                    Final_C.append(float(nmbs[2]))
                    FinalSC.append(float(nmbs[3]))
                    FinalSC2.append(float(nmbs[4]))

            b.append(bb)

            filt_D = remove_outliers(Final_D)
            filt_C = remove_outliers(Final_C)
            filt_SC = remove_outliers(FinalSC)
            filt_SC2 = remove_outliers(FinalSC2)

            mean_D, err_D = mean_and_error(filt_D)
            mean_C, err_C = mean_and_error(filt_C)
            mean_SC, err_SC = mean_and_error(filt_SC)
            mean_SC2, err_SC2 = mean_and_error(filt_SC2)

            D.append(mean_D)
            C.append(mean_C)
            SC.append(mean_SC)
            SC2.append(mean_SC2)

            D_err.append(err_D)
            C_err.append(err_C)
            SC_err.append(err_SC)
            SC2_err.append(err_SC2)

ax = plt.subplot(111)
box = ax.get_position()
ax.set_position([box.x0, box.y0, box.width, box.height * 0.8])

ax.errorbar(b, D, yerr=D_err, fmt='.-', color='red', markersize=2, capsize=3)
ax.errorbar(b, C, yerr=C_err, fmt='.-', color='blue', markersize=2, capsize=3)
ax.errorbar(b, SC, yerr=SC_err, fmt='.-', color='green', markersize=2, capsize=3)
ax.errorbar(b, SC2, yerr=SC2_err, fmt='.-', color='magenta', markersize=2, capsize=3)

# Explicitly setting legend labels here to avoid tikzplotlib issues
ax.legend(['D', 'C', r'$P_1$', r'$P_2$'], loc='upper center', bbox_to_anchor=(0.5, -0.1),
          fancybox=True, shadow=True, ncol=4)

ax.set_ylim([-0.1, 1.1])
ax.set_xlabel(r'$\beta$')
ax.set_ylabel('Fractions')

plt.grid(False)
tikzplotlib.save(t_name)