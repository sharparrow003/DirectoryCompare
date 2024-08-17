#! /bin/bash


case $1 in
	build)
		echo "Building code ..."
		mkdir -p build/
		cd build

		cmake -DCMAKE_CXX_COMPILER=g++-10 -DCMAKE_C_COMPILER=gcc-10 ..

		cmake --build .
	;;

	clean)
		echo "Cleaning code ..."
		rm -rf build/*
	;;

	run)
		echo "Running code ..."
		cd build/
		./DirComparator $2 $3
	;;

	*)
		echo "Incorrect usage"
		# TODO add user friendly message
	;;
esac