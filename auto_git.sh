#!/bin/sh
MY_NAME="Colin"
echo "Hello $MY_NAME - hope you're well."

#Waiting time
#echo "How long (in hour) do you want the program to sleep?"
hr=18

SEC=$(($hr*3600))
echo $SEC
sleep $SEC

#some command we need to do
#cd ..
python3 cat_final.py 1130_CP_Patch/M1 > CP_1_patent.dat 
python3 cat_final.py 1130_CP_Patch/M2 > CP_2_patent.dat 
python3 cat_final.py 1130_CP_Rand/M1 > CP_1_rand.dat 
python3 cat_final.py 1130_CP_Rand/M2 > CP_2_rand.dat 
git add CP_1_patent.dat CP_2_patent.dat CP_1_rand.dat CP_2_rand.dat


#commit message
commitmessage="Auto commit: $(date)"
echo $commitmessage
git add -u
git commit -m "$commitmessage" 
git push
