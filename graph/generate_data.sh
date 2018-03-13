#!/bin/bash
INPUTS="inputs_for_graphing.txt"

number_of_values=$(wc -l $INPUTS | cut -d' ' -f1)

i=1
while [ "$i" -le "$number_of_values" ]; do
  parameters=$(head -n $(($i + 1)) $INPUTS | tail -n 1)

  modulus=$(echo $parameters | cut -d' ' -f1)
  order=$(echo $parameters | cut -d' ' -f2)
  alpha=$(echo $parameters | cut -d' ' -f3)
  beta=$(echo $parameters | cut -d' ' -f4)
  result=$(echo $parameters | cut -d' ' -f5)

  input=$(mktemp)
  cat - << __EOF__ > $input
$modulus
$order
$alpha
$beta
__EOF__

  ../c/pollard $input 2>&1 >/dev/null
  number_of_calls=$(gprof ../c/pollard -b --exec-counts=f | cut -d' ' -f3)
  rm gmon.out
  echo "$modulus $order $alpha $beta $result $number_of_calls" >> data.txt

  i=$(($i + 1))
done
