static jint JNICALL cjni_api_register_target(JNIEnv *jvm_env, /* {{{ */
                                             jobject this, jobject o_name,
                                             jobject o_target) {
  return (cjni_api_register_match_target(jvm_env, this, o_name, o_target,
                                         CB_TYPE_TARGET));
}