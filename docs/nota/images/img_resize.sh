#!/bin/bash

if !command -v convert &> /dev/null;then
    echo "convert or imagemagick package not found"
    exit
fi

for i in `ls -1 originals/* | cut -d'/' -f2`;do
    echo "Resizing $i"
    convert -resize 30%  originals/$i ./$i
done

