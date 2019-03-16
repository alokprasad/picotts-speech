LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ttspico
LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuild-lib/armeabi-v7a/libttspico.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_CFLAGS   += -DANDROID27
APP_OPTIM := debug
LOCAL_MODULE := ttsdemo
LOCAL_SRC_FILES :=  $(LOCAL_PATH)/src/ttsdemo.cpp
LOCAL_SHARED_LIBRARIES := ttspico
LOCAL_C_INCLUDES := $(LOCAL_PATH)/src
LOCAL_LDFLAGS := -rpath /data/local
include $(BUILD_EXECUTABLE)


