static jint JNICALL cjni_api_dispatch_values(JNIEnv *jvm_env, /* {{{ */
                                             jobject this, jobject java_vl) {
  value_list_t vl = VALUE_LIST_INIT;
  int status;

  DEBUG("cjni_api_dispatch_values: java_vl = %p;", (void *)java_vl);

  status = jtoc_value_list(jvm_env, &vl, java_vl);
  if (status != 0) {
    ERROR("java plugin: cjni_api_dispatch_values: jtoc_value_list failed.");
    return -1;
  }

  status = plugin_dispatch_values(&vl);

  sfree(vl.values);

  return status;
}