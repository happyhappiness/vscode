static int jtoc_long(JNIEnv *jvm_env, /* {{{ */
                     jlong *ret_value, jclass class_ptr, jobject object_ptr,
                     const char *method_name) {
  jmethodID method_id;

  method_id = (*jvm_env)->GetMethodID(jvm_env, class_ptr, method_name, "()J");
  if (method_id == NULL) {
    ERROR("java plugin: jtoc_long: Cannot find method `long %s ()'.",
          method_name);
    return (-1);
  }

  *ret_value = (*jvm_env)->CallLongMethod(jvm_env, object_ptr, method_id);

  return (0);
}