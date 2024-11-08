#!/bin/sh
MY_NAME="Colin"
echo "Hello $MY_NAME - hope you're well."

#Waiting time
echo "How long (in hour) do you want the program to sleep?"
read hr

SEC=$($hr*3600)
echo $SEC
sleep $SEC

#some command we need to do
cd ..
python3 cat_final.py 1108New_m1 > mod_2.dat 
python3 cat_final.py 1108New_m0 > mod_1.dat 
git add mod_2.dat
git add mod_1.dat

#commit message
commitmessage="Auto commit: $(date)"
echo $commitmessage
git add -u
git commit -m "$commitmessage" 
git push
