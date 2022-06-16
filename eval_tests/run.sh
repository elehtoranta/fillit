#!/bin/bash
# Run this test script from './fillit/eval_tests'

TEST_DIR=eval_tests
# Update the binary
cd .. && make && make clean && cd ${TEST_DIR}

TEST_PATH=./test_files/
TEST_VALID=${TEST_PATH}valid/*
TEST_INVALID=${TEST_PATH}invalid/*
TEST_RESULT=test_results

rm -f ${TEST_RESULT}
echo -e "\n Starting tests for fillit...\n"

if [[ -z ${1+x} || $1 = 'v' || $1 = 'a' ]]; then
	echo -e "TESTING VALID INPUTS "
	for file in $TEST_VALID;
	do
		echo -e "Testing ${file#${TEST_VALID}} from ${TEST_VALID%/*}:"
		 { time ../fillit $file && echo ; } >> ${TEST_RESULT} 2>&1
	done
fi

if [[ -z ${1+x} || $1 = 'i' ||  $1 = 'a' ]]; then
	echo
	echo -e "TESTING INVALID INPUTS "
	for file in $TEST_INVALID;
	do
		echo -e "Testing ${file#${TEST_INVALID}} from ${TEST_INVALID%/*}:"
		 { time ../fillit $file && echo ; } >> ${TEST_RESULT} 2>&1
	done
fi
