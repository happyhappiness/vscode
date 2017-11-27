static int ctoj_int (JNIEnv *jvm_env, /* {{{ */
    jint value,
    jclass class_ptr, jobject object_ptr, const char *method_name)
{
  jmethodID m_set;

  /* Search for the `void setFoo (int i)' method. */
  m_set = (*jvm_env)->GetMethodID (jvm_env, class_ptr,
      method_name, "(I)V");
  if (m_set == NULL)
  {
    ERROR ("java plugin: ctoj_int: Cannot find method `void %s (int)'.",
        method_name);
    return (-1);
  }

  (*jvm_env)->CallVoidMethod (jvm_env, object_ptr, m_set, value);

  return (0);
}