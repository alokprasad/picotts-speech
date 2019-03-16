LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_MODULE := svoxpico
#LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuild-lib/armeabi-v7a/libttspico.so
LOCAL_SRC_FILES := $(LOCAL_PATH)/picotts-src/libs/$(TARGET_ARCH_ABI)/libsvoxpico.so
include $(PREBUILT_SHARED_LIBRARY)



include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_MODULE := expat
#LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuild-lib/armeabi-v7a/libttspico.so
LOCAL_SRC_FILES := $(LOCAL_PATH)/lib/libexpat.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_MODULE := libttscompat
LOCAL_SHARED_LIBRARIES := svoxpico libexpat
#LOCAL_SHARED_LIBRARIES := svoxpico
LOCAL_SRC_FILES := \
        src/strdup16to8.cpp \
        src/strdup8to16.cpp  \
	src/svox_ssml_parser.cpp \
	src/com_svox_picottsengine.cpp

LOCAL_C_INCLUDES := \
        include picotts-src

#LOCAL_LDFLAGS := -rpath /data/local
include $(BUILD_SHARED_LIBRARY)
