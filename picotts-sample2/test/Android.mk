LOCAL_PATH := $(call my-dir)
#$(warning Local path is $(LOCAL_PATH))	
#include $(CLEAR_VARS)


include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_MODULE := ttscompat
#LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuild-lib/armeabi-v7a/libttspico.so
LOCAL_SRC_FILES := $(LOCAL_PATH)/../libs/$(TARGET_ARCH_ABI)/libttscompat.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_MODULE := expat
#LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuild-lib/armeabi-v7a/libttspico.so
LOCAL_SRC_FILES := $(LOCAL_PATH)/../libs/$(TARGET_ARCH_ABI)/libexpat.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_MODULE := svoxpico
#LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuild-lib/armeabi-v7a/libttspico.so
LOCAL_SRC_FILES := $(LOCAL_PATH)/../libs/$(TARGET_ARCH_ABI)/libsvoxpico.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_MODULE := testpico
LOCAL_SRC_FILES := testpico.cpp
LOCAL_SHARED_LIBRARIES := ttscompat svoxpico expat
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../picotts-src
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../picotts-src
#LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/compat/include
LOCAL_LDFLAGS := -rpath /data/local
include $(BUILD_EXECUTABLE)

#ndk-build APP_ABI=x86

