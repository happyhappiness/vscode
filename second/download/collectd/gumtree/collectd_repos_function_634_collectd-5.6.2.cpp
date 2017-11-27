static int jtoc_value(JNIEnv *jvm_env, /* {{{ */
                      value_t *ret_value, int ds_type, jobject object_ptr) {
  jclass class_ptr;
  int status;

  class_ptr = (*jvm_env)->GetObjectClass(jvm_env, object_ptr);

  if (ds_type == DS_TYPE_GAUGE) {
    jdouble tmp_double;

    status =
        jtoc_double(jvm_env, &tmp_double, class_ptr, object_ptr, "doubleValue");
    if (status != 0) {
      ERROR("java plugin: jtoc_value: "
            "jtoc_double failed.");
      return (-1);
    }
    (*ret_value).gauge = (gauge_t)tmp_double;
  } else {
    jlong tmp_long;

    status = jtoc_long(jvm_env, &tmp_long, class_ptr, object_ptr, "longValue");
    if (status != 0) {
      ERROR("java plugin: jtoc_value: "
            "jtoc_long failed.");
      return (-1);
    }

    if (ds_type == DS_TYPE_DERIVE)
      (*ret_value).derive = (derive_t)tmp_long;
    else if (ds_type == DS_TYPE_ABSOLUTE)
      (*ret_value).absolute = (absolute_t)tmp_long;
    else
      (*ret_value).counter = (counter_t)tmp_long;
  }

  return (0);
}