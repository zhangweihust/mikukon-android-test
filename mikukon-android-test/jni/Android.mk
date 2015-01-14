# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
APP_OPTIM:= debug

LOCAL_PATH := $(call my-dir)
LOCAL_CFLAGS := -g
LOCAL_CFLAGS += -ggdb
LOCAL_CFLAGS += -fPIC

include $(CLEAR_VARS)
LOCAL_MODULE    := test 
LOCAL_SRC_FILES	:=	test.cpp 
LOCAL_LDLIBS:= -llog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= substrate
LOCAL_SRC_FILES := libsubstrate.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := ghost 
LOCAL_SRC_FILES	:=	ghost.cpp
#LOCAL_SHARED_LIBRARIES := substrate
LOCAL_LDLIBS := -L$(LOCAL_PATH) -lsubstrate -llog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := hook 
LOCAL_SRC_FILES	:=	hook.cpp
#LOCAL_SHARED_LIBRARIES := substrate
LOCAL_LDLIBS := -L$(LOCAL_PATH) -lsubstrate -llog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := inject
LOCAL_SRC_FILES	:=	main.c \
        injectso.c \
		ptrace_tools.c \
		shellcode.s
LOCAL_LDLIBS := -L$(LOCAL_PATH) 
include $(BUILD_EXECUTABLE) 

#include $(CLEAR_VARS)
#LOCAL_MODULE    := md5test
#LOCAL_SRC_FILES	:=	md5test.cpp 
#LOCAL_LDLIBS := -L$(LOCAL_PATH) 
#include $(BUILD_EXECUTABLE) 



include $(CLEAR_VARS)
LOCAL_MODULE    := ptrace
LOCAL_SRC_FILES	:=	ptrace.c 
LOCAL_LDLIBS := -L$(LOCAL_PATH) 
include $(BUILD_EXECUTABLE) 

