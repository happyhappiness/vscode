static int jtoc_string(JNIEnv *jvm_env, /* {{{ */
                       char *buffer, size_t buffer_size, int empty_okay,
                       jclass class_ptr, jobject object_ptr,
                       const char *method_name) {
  jmethodID method_id;
  jobject string_obj;
  const char *c_str;

  method_id = (*jvm_env)->GetMethodID(jvm_env, class_ptr, method_name,
                                      "()Ljava/lang/String;");
  if (method_id == NULL) {
    ERROR("java plugin: jtoc_string: Cannot find method `String %s ()'.",
          method_name);
    return (-1);
  }

  string_obj = (*jvm_env)->CallObjectMethod(jvm_env, object_ptr, method_id);
  if ((string_obj == NULL) && (empty_okay == 0)) {
    ERROR("java plugin: jtoc_string: CallObjectMethod (%s) failed.",
          method_name);
    return (-1);
  } else if ((string_obj == NULL) && (empty_okay != 0)) {
    memset(buffer, 0, buffer_size);
    return (0);
  }

  c_str = (*jvm_env)->GetStringUTFChars(jvm_env, string_obj, 0);
  if (c_str == NULL) {
    ERROR("java plugin: jtoc_string: GetStringUTFChars failed.");
    (*jvm_env)->DeleteLocalRef(jvm_env, string_obj);
    return (-1);
  }

  sstrncpy(buffer, c_str, buffer_size);

  (*jvm_env)->ReleaseStringUTFChars(jvm_env, string_obj, c_str);
  (*jvm_env)->DeleteLocalRef(jvm_env, string_obj);

  return (0);
}