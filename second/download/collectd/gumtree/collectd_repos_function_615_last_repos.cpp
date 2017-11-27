static jobject ctoj_jlong_to_number(JNIEnv *jvm_env, jlong value) /* {{{ */
{
  jclass c_long;
  jmethodID m_long_constructor;

  /* Look up the java.lang.Long class */
  c_long = (*jvm_env)->FindClass(jvm_env, "java/lang/Long");
  if (c_long == NULL) {
    ERROR("java plugin: ctoj_jlong_to_number: Looking up the "
          "java.lang.Long class failed.");
    return NULL;
  }

  m_long_constructor =
      (*jvm_env)->GetMethodID(jvm_env, c_long, "<init>", "(J)V");
  if (m_long_constructor == NULL) {
    ERROR("java plugin: ctoj_jlong_to_number: Looking up the "
          "`Long (long)' constructor failed.");
    return NULL;
  }

  return (*jvm_env)->NewObject(jvm_env, c_long, m_long_constructor, value);
}