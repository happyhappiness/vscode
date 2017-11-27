static jint JNICALL cjni_api_register_match (JNIEnv *jvm_env, /* {{{ */
    jobject this, jobject o_name, jobject o_match)
{
  return (cjni_api_register_match_target (jvm_env, this, o_name, o_match,
        CB_TYPE_MATCH));
}