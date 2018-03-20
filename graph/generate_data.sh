#!/bin/bash
INPUTS="Inputs/inputs_for_graphing_1.txt"

number_of_values=$(wc -l $INPUTS | cut -d' ' -f1)

i=1
while [ "$i" -le "$number_of_values" ]; do
  parameters=$(head -n $i $INPUTS | tail -n 1)

  modulus=$(echo $parameters | cut -d' ' -f1)
  order=$(echo $parameters | cut -d' ' -f2)
  g=$(echo $parameters | cut -d' ' -f3)
  h=$(echo $parameters | cut -d' ' -f4)
  result=$(echo $parameters | cut -d' ' -f5)

  input=$(mktemp)
  cat - << __EOF__ > $input
$modulus
$order
$g
$h
__EOF__

  ../c/pollard $input 2>&1 >/dev/null
  number_of_calls=$(gprof ../c/pollard -b --exec-counts=f | cut -d' ' -f3)
  rm gmon.out
  echo "$modulus $order $g $h $result $number_of_calls" >> Outputs/data_1.txt

  i=$(($i + 1))
done
