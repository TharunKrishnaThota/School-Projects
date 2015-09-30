#!/bin/bash

if [ $1 == "update" ]; then
    wget -O index.html www.youtube.com
elif [ $1 == "rm" ]; then
    rm views.txt duration.txt title.txt title1.txt user.txt final.csv;
elif [ $1 == "paste" ]; then
    paste -d"," views.txt duration.txt title.txt user.txt | sort -nr > final.csv
else
    grep views index.html | while read x; 
    do views=`expr "$x" : ".*<li>\(.*\) views<\/li>.*"`; 
	echo ${views//,/} >> views.txt; 
    done;

    grep Duration index.html | while read x; 
    do duration=`expr "$x" : ".*Duration: \(.*\)\.<\/span>.*"`; 
	echo ${duration} >> duration.txt; 
    done;

    grep title index.html | while read x; 
    do title=`expr "$x" : ".* title=\"\(.*\)\" aria-describedby=\".*"`; 
	echo ${title//,/} >> title.txt; 
    done; 
    uniq -u title.txt > title1.txt;
    cat title1.txt | tr -d [\#\&\$\;] > title.txt;

    grep user index.html | while read x; 
    do user=`expr "$x" : ".*\/user\/\(.*\)\" class=\" yt-uix-sessionlink     spf-link  g-hovercard\".*"`; 
	echo $user >> user.txt; 
    done;
fi






