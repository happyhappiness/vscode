static jint JNICALL cjni_api_register_shutdown(JNIEnv *jvm_env, /* {{{ */
                                               jobject this, jobject o_name,
                                               jobject o_shutdown) {
  return cjni_callback_register(jvm_env, o_name, o_shutdown, CB_TYPE_SHUTDOWN);
}