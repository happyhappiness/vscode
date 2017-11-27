static jstring JNICALL cjni_api_get_hostname(JNIEnv *jvm_env, jobject this) {
  return ctoj_output_string(jvm_env, hostname_g);
}