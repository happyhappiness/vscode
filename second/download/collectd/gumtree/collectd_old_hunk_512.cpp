
  plugin_log (severity, "%s", c_str);

  (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_message, c_str);
} /* }}} void cjni_api_log */

/* List of ``native'' functions, i. e. C-functions that can be called from
 * Java. */
static JNINativeMethod jni_api_functions[] = /* {{{ */
{
  { "dispatchValues",
    "(Lorg/collectd/api/ValueList;)I",
