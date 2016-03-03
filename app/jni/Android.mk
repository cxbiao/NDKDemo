 LOCAL_PATH := $(call my-dir)

   include $(CLEAR_VARS)
  
  #要生成的类库名
   LOCAL_MODULE    := nativeProcess
  #c源文件名
   LOCAL_SRC_FILES :=\
     $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/src/utils/*.cpp))  \
     $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/src/*.cpp))

  LOCAL_C_INCLUDES += $(LOCAL_PATH)/src
  LOCAL_C_INCLUDES += $(LOCAL_PATH)/src/utils
   LOCAL_LDLIBS := -llog
   include $(BUILD_SHARED_LIBRARY)