#!/bin/sh

echo "Building"
make

echo "Expecting 1:"
echo ""
for test in ./tests/1-*; do
	echo "	$test"
	(./main "$test");
done

echo ""
echo "Expecting 2:"
echo ""

for test in ./tests/2-*; do
	echo "	$test"
	(./main "$test");
done
