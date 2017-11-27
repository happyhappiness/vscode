static int ctoj_value_list_add_value (JNIEnv *jvm_env, /* {{{ */
    value_t value, int ds_type,
    jclass class_ptr, jobject object_ptr)
{
  jmethodID m_addvalue;
  jobject o_number;

  m_addvalue = (*jvm_env)->GetMethodID (jvm_env, class_ptr,
      "addValue", "(Ljava/lang/Number;)V");
  if (m_addvalue == NULL)
  {
    ERROR ("java plugin: ctoj_value_list_add_value: "
        "Cannot find method `void addValue (Number)'.");
    return (-1);
  }

  o_number = ctoj_value_to_number (jvm_env, value, ds_type);
  if (o_number == NULL)
  {
    ERROR ("java plugin: ctoj_value_list_add_value: "
        "ctoj_value_to_number failed.");
    return (-1);
  }

  (*jvm_env)->CallVoidMethod (jvm_env, object_ptr, m_addvalue, o_number);

  (*jvm_env)->DeleteLocalRef (jvm_env, o_number);

  return (0);
}