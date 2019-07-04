#include "DeviceServices.h"
#include "platform/android/jni/JniHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#endif
void DeviceServices::showToastMessage(string iMsg) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "jniShowToastMessage", "(Ljava/lang/String;)V")) {
        jstring msg = methodInfo.env->NewStringUTF(iMsg.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, msg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        return;
    }
#endif
}
