#!/bin/sh
MY_NAME="Colin"
echo "Hello $MY_NAME - hope you're well."

#Waiting time
read hr

SEC=$(echo "scale=2; $hr*3600" | bc)
echo $SEC
sleep $SEC

#some command we need to do

#commit message
commitmessage="Auto commit: $(date)"
echo $commitmessage
git add -u
git commit -m "$commitmessage" 
git push