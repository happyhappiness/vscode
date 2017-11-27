static int ctoj_long(JNIEnv *jvm_env, /* {{{ */
                     jlong value, jclass class_ptr, jobject object_ptr,
                     const char *method_name) {
  jmethodID m_set;

  /* Search for the `void setFoo (long l)' method. */
  m_set = (*jvm_env)->GetMethodID(jvm_env, class_ptr, method_name, "(J)V");
  if (m_set == NULL) {
    ERROR("java plugin: ctoj_long: Cannot find method `void %s (long)'.",
          method_name);
    return (-1);
  }

  (*jvm_env)->CallVoidMethod(jvm_env, object_ptr, m_set, value);

  return (0);
}