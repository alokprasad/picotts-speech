LOCAL_PATH := $(call my-dir)
#$(warning Local path is $(LOCAL_PATH))	
#include $(CLEAR_VARS)


include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_MODULE := svoxpico
#LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuild-lib/armeabi-v7a/libttspico.so
LOCAL_SRC_FILES := $(LOCAL_PATH)/../picotts-src/libs/$(TARGET_ARCH_ABI)/libsvoxpico.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_MODULE := pico2wave
LOCAL_SRC_FILES :=  src/pico2wave.c
LOCAL_STATIC_LIBRARIES := svoxpico
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../picotts-src
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../picotts-src
#LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/compat/include
LOCAL_LDFLAGS := -rpath /data/local
include $(BUILD_EXECUTABLE)

#ndk-build APP_ABI=x86
