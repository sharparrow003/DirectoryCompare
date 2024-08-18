#! /bin/bash

currentDir=$(pwd)
a_dir=$currentDir/$2
b_dir=$currentDir/$3

echo $a_dir
echo $b_dir

case $1 in
	build)
		echo "Building code ..."
		mkdir -p build/
		cd build

		cmake -DCMAKE_CXX_COMPILER=g++-10 -DCMAKE_C_COMPILER=gcc-10 ..

		cmake --build .
	;;

	clean)
		echo "Cleaning code and test data ..."
		rm -rf build/*
		rm -rf test_data/*
	;;

	run)
		echo "Running code ..."
		cd build/
		./DirComparator $a_dir $b_dir
	;;

	*)
		echo "Incorrect usage"
		# TODO add user friendly message
	;;
esac