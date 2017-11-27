static int jtoc_double(JNIEnv *jvm_env, /* {{{ */
                       jdouble *ret_value, jclass class_ptr, jobject object_ptr,
                       const char *method_name) {
  jmethodID method_id;

  method_id = (*jvm_env)->GetMethodID(jvm_env, class_ptr, method_name, "()D");
  if (method_id == NULL) {
    ERROR("java plugin: jtoc_double: Cannot find method `double %s ()'.",
          method_name);
    return (-1);
  }

  *ret_value = (*jvm_env)->CallDoubleMethod(jvm_env, object_ptr, method_id);

  return (0);
}