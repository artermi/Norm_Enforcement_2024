import sys
import os
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict



d_name = sys.argv[1]

for root,dirs,files in sorted(os.walk(d_name,topdown = False)):

	for name in sorted(files):
		if name.find('.dat') >= 0 and not ( name.find('_i_') >= 0):
			# A_0100_B_0200_C_0100_D_0100_E_0100_F_0100.dat
            # r_0300_b_0050_g_0080_mod_00.dat
			# 0123456789|123456789|123456789|123456789|
			a = float(name[ 2: 6])/100
			b = float(name[ 9:13])/100
			l = float(name[16:20])/100

			with open(os.path.join(root, name)) as file:
				for last_line in file:
					pass
				nmbs = last_line.split()

			print('({},{},{}) = ({},{},{},{})'.format(a,b,l,nmbs[1],nmbs[2],nmbs[3],nmbs[4]))


