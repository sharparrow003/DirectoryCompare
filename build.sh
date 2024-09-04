#! /bin/bash

currentDir=$(pwd)
a_dir=$currentDir/$2
b_dir=$currentDir/$3

clean() {
	echo "Cleaning build dir ..."
	rm -rf build/
}

clean_test_data() {
	echo "Cleaning test data ..."
	rm -rf test_data/
}

case $1 in
	build)
		echo "Building code ..."
		mkdir -p build/
		cd build

		cmake -DCMAKE_CXX_COMPILER=g++-10 -DCMAKE_C_COMPILER=gcc-10 ..

		cmake --build .
	;;
	run)
		echo "Running code ..."
		cd build/
		./DirComparator $a_dir $b_dir
	;;
	build_unit_tests)
		echo "Building code with unit tests ..."
		mkdir -p build/
		cd build

		cmake -DCMAKE_CXX_COMPILER=g++-10 -DCMAKE_C_COMPILER=gcc-10 -DUNIT_TESTS=ON .. 

		cmake --build .
	;;
	run_unit_tests)
		cd build
		ctest -V
	;;
	create_test_data)
		echo "Creating sample test data ..."
		python3 generate_test_data.py
	;;

	clean)
		clean
	;;
	clean_test_data)
		clean_test_data
	;;
	clean_all)
		clean
		clean_test_data
	;;

	*)
		echo ""
		echo "Incorrect usage. Please use ./build.sh <action> <args if applicable>"
		echo ""
		echo "Supported actions:"
		echo "1. build: Builds code"
		echo "2. run: Runs built code. Pass dirA and dirB as args. Example: ./build.sh run test_data/files_a/ test_data/files_b/"
		echo "3. create_test_data: Creates test data"
		echo "4. clean: Cleans build dir"
		echo "5. clean_test_data: Cleans test data"
		echo "6. clean_all: Cleans both build dir and test data"
	;;
esac