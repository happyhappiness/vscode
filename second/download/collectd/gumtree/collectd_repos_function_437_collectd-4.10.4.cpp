static int ctoj_double (JNIEnv *jvm_env, /* {{{ */
    jdouble value,
    jclass class_ptr, jobject object_ptr, const char *method_name)
{
  jmethodID m_set;

  /* Search for the `void setFoo (double d)' method. */
  m_set = (*jvm_env)->GetMethodID (jvm_env, class_ptr,
      method_name, "(D)V");
  if (m_set == NULL)
  {
    ERROR ("java plugin: ctoj_double: Cannot find method `void %s (double)'.",
        method_name);
    return (-1);
  }

  (*jvm_env)->CallVoidMethod (jvm_env, object_ptr, m_set, value);

  return (0);
}