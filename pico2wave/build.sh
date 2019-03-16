#build

if [ "$1" == "linux" ]; then
        echo "Building pico2wave for Linux(32)"
        make
elif [ "$1" == "android" ] ;then
        echo "Building pico2wave for Android(32)"
        ndk-build APP_BUILD_SCRIPT=Android.mk NDK_APPLICATION_MK=Application.mk NDK_PROJECT_PATH=.
elif [ "$1" == "clean" ] ;then
        echo "Cleaning..."
        ndk-build APP_BUILD_SCRIPT=Android.mk NDK_PROJECT_PATH=. clean
        make clean
        rm -rf obj
        rm -rf libs
else
        echo "Usage :sh build.sh <linux|android|clean>"

fi

#commit
#rm -rf obj
#rm -rf libs

