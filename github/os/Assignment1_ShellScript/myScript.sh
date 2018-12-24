#!/bin/bash
# The line above makes your script executable.
# You should write your tutorial in here.
# Include comments inline with your script explaining what is going on.

# You might start out by first saying the purpose of the script and
# demonstrating its usage.

<<<<<<< HEAD
# Problem Statement: "In this assignment, I am going to download a csv file from a website, and sort the csv file 
# in some particular order, and print out the sorted result."
# usage: sh myScript.sh

# use cd access to the desktop
=======
# Problem Statement: "In this assignment, I am going to download a csv file from a website, and sort the csv f$
# in some particular order, and print out the sorted result."
# usage: sh myScript.sh

# use command cd access to the desktop
>>>>>>> 1621eecf948d3100ca87f37c805ea1122957924c
cd Desktop

# to see what I have in the desktop
ls

#  download a csv file from a website
<<<<<<< HEAD
=======
# command curl, a tool to transfer data from a website to computer
# command -O means download the exact type and name
>>>>>>> 1621eecf948d3100ca87f37c805ea1122957924c
curl -O http://insight.dev.schoolwires.com/HelpAssets/C2Assets/C2Files/C2ImportGroupsSample.csv

# use ls to see what’s downloaded
ls

# rename the file to a simple name: sample
<<<<<<< HEAD
mv C2ImportGroupsSample.csv sample.csv

# display the file by cat command
cat sample.csv

# sort the fourth column
cut -f 4 -d , sample.csv |sort --ignore-case

# use loop to sort the top 5 people in ascending order
=======
# command mv means changing the file name, or directories
mv C2ImportGroupsSample.csv sample.csv

# display the file by cat command
# cat is a standard utility that reads and output a file
cat sample.csv

# sort the fourth column
# command cut "cut" the table 
# command -f, 4 means field 4, or the 4th column in the table
# command -d , means divison by ","
# command sort --ignore-case means sorting with ignoring the cases
cut -f 4 -d , sample.csv |sort --ignore-case

# use loop to sort the top 5 people in ascending order
# loop through the lines we "cut", which is inside the $()
# in the loop we "do"
# grep command used to get the information
# head - n 6 means the top 5 data
# done to end the loop

>>>>>>> 1621eecf948d3100ca87f37c805ea1122957924c
for i in $(cut -f 4 -d , sample.csv |sort --ignore-case)
do
grep -F -i "$i" sample.csv | head -n 6
done


<<<<<<< HEAD


=======
>>>>>>> 1621eecf948d3100ca87f37c805ea1122957924c
