#!/bin/bash
# Run this test script from './fillit/tests'

# Update the binary
cd .. && make && make clean && cd tests

TEST_PATH=./test_files/
TEST_VALID=${TEST_PATH}valid/*
TEST_INVALID=${TEST_PATH}invalid/*

echo -e "\n Starting tests for fillit...\n"

if [[ -z ${1+x} || $1 = 'v' || $1 = 'a' ]]; then
	echo -e "TESTING VALID INPUTS "
	for file in $TEST_VALID;
	do
		echo -e "Testing ${file#${TEST_VALID}} from ${TEST_VALID%/*}:"
		../fillit $file | grep --color='auto' ERROR
	done
fi

if [[ -z ${1+x} || $1 = 'i' ||  $1 = 'a' ]]; then
	echo
	echo -e "TESTING INVALID INPUTS "
	for file in $TEST_INVALID;
	do
		echo -e "Testing ${file#${TEST_INVALID}} from ${TEST_INVALID%/*}:"
		../fillit $file | grep --color='auto' ERROR
		echo
	done
fi
