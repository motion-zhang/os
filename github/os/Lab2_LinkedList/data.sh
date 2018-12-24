#!/bin/bash

# Use this script to scrape data from the web using the provided shell scripts provided.

# Win column from Red Sox data
curl -s http://www.ccs.neu.edu/home/awjacks/cs3650f18/Labs/2/red_sox_history.csv | awk -F ',' '{ if (NR > 2)  { print $5 } }' > sox_wins.txt 
