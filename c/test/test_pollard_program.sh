#!/bin/bash

test_different_precomputed_values() {
    number_of_values=$(wc -l fixtures/inputs.txt | cut -d' ' -f1)

    i=1
    while [ "$i" -le "$number_of_values" ]; do
        parameters=$(head -n $(($i + 1)) fixtures/inputs.txt | tail -n 1)

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

        expected_message="Log of $beta in base $alpha = $result"
        message=$(../pollard $input)

        assert_equals "$expected_message" "$message"

        i=$(($i + 1))
    done
}
