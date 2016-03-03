 LOCAL_PATH := $(call my-dir)

   include $(CLEAR_VARS)
  
  #要生成的类库名
   LOCAL_MODULE    := nativeProcess
  #c源文件名
   LOCAL_SRC_FILES := NativeProcess.c
   LOCAL_LDLIBS := -llog
   include $(BUILD_SHARED_LIBRARY)