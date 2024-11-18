#!/bin/sh
MY_NAME="Colin"
echo "Hello $MY_NAME - hope you're well."

#Waiting time
#echo "How long (in hour) do you want the program to sleep?"
hr=1

SEC=$(($hr*3600))
echo $SEC
sleep $SEC

#some command we need to do
cd ..
python3 cat_final.py 1118_m0_patent > mod_0_patent.dat 
python3 cat_final.py 1118_m1_patent > mod_1_patent.dat 
git add mod_0_patent.dat
git add mod_1_patent.dat

#commit message
commitmessage="Auto commit: $(date)"
echo $commitmessage
git add -u
git commit -m "$commitmessage" 
git push
