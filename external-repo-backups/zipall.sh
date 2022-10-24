#!/bin/bash
files=$(ls -1d */ | sed 's/\///g')
for n in $files
do
    7z a $n.7z $n 
done
