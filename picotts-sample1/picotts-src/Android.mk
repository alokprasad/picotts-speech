# Build Base Generic SVOX Pico Library

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
APP_OPTIM := debug

LOCAL_MODULE := libsvoxpico
LOCAL_MULTILIB := 32

LOCAL_SRC_FILES := $(wildcard $(LOCAL_PATH)/src/*.c)

LOCAL_CFLAGS+= $(TOOL_CFLAGS)
LOCAL_LDFLAGS+= $(TOOL_LDFLAGS)

#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)




