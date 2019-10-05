#!/bin/bash
tr '()' ::<test|sed -r 's/^([0-9]+)[a-z ]*([0-9]*)[a-z ]*:?(.*:)?[a-z ]*([0-9]*) ([a-z]*)[a-z ]*([0-9]*)/\1:\2:\3\4:\5:\6/;s/ to /-/g'
#to format the input for the py script
