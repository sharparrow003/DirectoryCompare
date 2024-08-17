#! /bin/bash


case $1 in
	build)
		echo "Building code ..."
		mkdir -p build/
		cd build

		cmake ..

		cmake --build .
	;;

	clean)
		echo "Cleaning code ..."
		rm -rf build/*
	;;

	run)
		echo "Running code ..."
		cd build/
		./DirComparator
	;;

	*)
		echo "Incorrect usage"
		# TODO add user friendly message
	;;
esac