static int jtoc_int (JNIEnv *jvm_env, /* {{{ */
    jint *ret_value,
    jclass class_ptr, jobject object_ptr, const char *method_name)
{
  jmethodID method_id;

  method_id = (*jvm_env)->GetMethodID (jvm_env, class_ptr,
      method_name, "()I");
  if (method_id == NULL)
  {
    ERROR ("java plugin: jtoc_int: Cannot find method `int %s ()'.",
        method_name);
    return (-1);
  }

  *ret_value = (*jvm_env)->CallIntMethod (jvm_env, object_ptr, method_id);

  return (0);
}