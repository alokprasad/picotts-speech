#!/bin/bash

if [ "$1" == "linux" ]; then
	echo "Building libsvoxpico.so for Linux(32)"
	make
	echo "*****Copy libsvoxpico.so to /usr/lib/i386-linux-gnu/libsvoxpico.so****"
elif [ "$1" == "android" ] ;then
	echo "Building libsvoxpico.so for Android(32)"
	ndk-build APP_BUILD_SCRIPT=Android.mk NDK_APPLICATION_MK=Application.mk NDK_PROJECT_PATH=.
elif [ "$1" == "clean" ] ;then
	echo "Cleaning..."
	ndk-build APP_BUILD_SCRIPT=Android.mk NDK_PROJECT_PATH=. clean
	make clean
	rm -rf obj
	rm -rf libs
else
	echo "Usage :sh build-pico.sh <linux|android|clean>"

fi
