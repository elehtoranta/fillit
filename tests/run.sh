#!/bin/bash
# Run this test script from './fillit/tests'

BOLDRED='\e[1;31m'
BOLDGREEN='\e[1;32m'
RESET='\e[0m'

# Update the binary
cd .. && make && make clean && cd tests

TEST_PATH=./test_files/
TEST_VALID=${TEST_PATH}valid/*
TEST_INVALID=${TEST_PATH}invalid/*

echo -e "\n ${BOLDGREEN}Starting tests for fillit...\n${RESET}"
echo -e "${BOLDGREEN} TESTING VALID INPUTS ${RESET}"
for file in $TEST_VALID;
do
	echo -e "Testing ${file#${TEST_VALID}} from ${TEST_VALID%/*}:"
	../fillit $file | grep --color='auto' ERROR
done

if [ $# == 1 ]; then

	echo
	echo -e "${BOLDRED} TESTING INVALID INPUTS ${RESET}"
	for file in $TEST_INVALID;
	do
		echo -e "Testing ${file#${TEST_INVALID}} from ${TEST_INVALID%/*}:"
		../fillit $file | grep --color='auto' ERROR
		echo
	done
else
	echo -e "\nGive an argument if you want to test for invalid inputs."
fi
