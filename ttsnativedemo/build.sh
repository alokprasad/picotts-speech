#!/bin/bash

if [ "$1" == "android" ] ;then
	echo "Building ttsdemo for Android(32)"
	ndk-build APP_BUILD_SCRIPT=Android.mk NDK_APPLICATION_MK=Application.mk NDK_PROJECT_PATH=.
elif [ "$1" == "clean" ] ;then
	echo "Cleaning..."
	ndk-build APP_BUILD_SCRIPT=Android.mk NDK_PROJECT_PATH=. clean
	#make clean
	rm -rf obj
	rm -rf libs
else
	echo "Usage :sh build-pico.sh <android|clean>"

fi
