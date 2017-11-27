static int ctoj_string (JNIEnv *jvm_env, /* {{{ */
    const char *string,
    jclass class_ptr, jobject object_ptr, const char *method_name)
{
  jmethodID m_set;
  jstring o_string;

  /* Create a java.lang.String */
  o_string = (*jvm_env)->NewStringUTF (jvm_env,
      (string != NULL) ? string : "");
  if (o_string == NULL)
  {
    ERROR ("java plugin: ctoj_string: NewStringUTF failed.");
    return (-1);
  }

  /* Search for the `void setFoo (String s)' method. */
  m_set = (*jvm_env)->GetMethodID (jvm_env, class_ptr,
      method_name, "(Ljava/lang/String;)V");
  if (m_set == NULL)
  {
    ERROR ("java plugin: ctoj_string: Cannot find method `void %s (String)'.",
        method_name);
    (*jvm_env)->DeleteLocalRef (jvm_env, o_string);
    return (-1);
  }

  /* Call the method. */
  (*jvm_env)->CallVoidMethod (jvm_env, object_ptr, m_set, o_string);

  /* Decrease reference counter on the java.lang.String object. */
  (*jvm_env)->DeleteLocalRef (jvm_env, o_string);

  return (0);
}