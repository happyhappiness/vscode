static jobject ctoj_jdouble_to_number(JNIEnv *jvm_env, jdouble value) /* {{{ */
{
  jclass c_double;
  jmethodID m_double_constructor;

  /* Look up the java.lang.Long class */
  c_double = (*jvm_env)->FindClass(jvm_env, "java/lang/Double");
  if (c_double == NULL) {
    ERROR("java plugin: ctoj_jdouble_to_number: Looking up the "
          "java.lang.Double class failed.");
    return NULL;
  }

  m_double_constructor =
      (*jvm_env)->GetMethodID(jvm_env, c_double, "<init>", "(D)V");
  if (m_double_constructor == NULL) {
    ERROR("java plugin: ctoj_jdouble_to_number: Looking up the "
          "`Double (double)' constructor failed.");
    return NULL;
  }

  return (*jvm_env)->NewObject(jvm_env, c_double, m_double_constructor, value);
}