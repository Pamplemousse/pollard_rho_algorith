#!/bin/bash
INPUTS="fixtures/inputs.txt"

test_different_precomputed_values() {
    number_of_values=$(wc -l $INPUTS | cut -d' ' -f1)

    i=1
    while [ "$i" -le "$number_of_values" ]; do
        parameters=$(head -n $(($i + 1)) $INPUTS | tail -n 1)

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

        expected_message="Log of $h in base $g = $result"
        message=$(../pollard $input)

        assert_equals "$expected_message" "$message"

        i=$(($i + 1))
    done
}

# TODO: more generic
#   this test relies only on the handbook values passed via the `input.txt` file
test_number_of_calls_to_the_iteration_function() {
    ../pollard ../input.txt 2>&1 >/dev/null
    number_of_calls=$(gprof ../pollard -b --exec-counts=f | cut -d' ' -f3)

    # f function is called 3 times per cycle
    relative_number_of_calls=$((number_of_calls / 3))

    assert_equals "14" "$relative_number_of_calls"
}
