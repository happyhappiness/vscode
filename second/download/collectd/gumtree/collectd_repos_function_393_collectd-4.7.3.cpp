static jint JNICALL cjni_api_register_init (JNIEnv *jvm_env, /* {{{ */
    jobject this, jobject o_name, jobject o_config)
{
  return (cjni_callback_register (jvm_env, o_name, o_config, CB_TYPE_INIT));
}