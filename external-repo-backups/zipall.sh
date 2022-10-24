#!/bin/bash
files=$(ls -1d */ | sed 's/\///g')
for n in $files
do
    rm -rf $n/.git
    7z a $n.7z $n 
done
