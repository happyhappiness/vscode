static void JNICALL cjni_api_log (JNIEnv *jvm_env, /* {{{ */
    jobject this, jint severity, jobject o_message)
{
  const char *c_str;

  c_str = (*jvm_env)->GetStringUTFChars (jvm_env, o_message, 0);
  if (c_str == NULL)
  {
    ERROR ("java plugin: cjni_api_log: GetStringUTFChars failed.");
    return;
  }

  if (severity < LOG_ERR)
    severity = LOG_ERR;
  if (severity > LOG_DEBUG)
    severity = LOG_DEBUG;

  plugin_log (severity, "%s", c_str);

  (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_message, c_str);
}