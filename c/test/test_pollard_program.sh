#!/bin/bash
INPUTS="fixtures/inputs.txt"

test_different_precomputed_values() {
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

        h_in_decimal=$(echo "$((2#${h}))")
        g_in_decimal=$(echo "$((2#${g}))")
        result_in_decimal=$(echo "$((2#${result}))")

        expected_message="Log of $h_in_decimal in base $g_in_decimal = $result_in_decimal"
        message=$(../pollard $input)

        assert_equals "$expected_message" "$message"

        i=$(($i + 1))
    done
}
