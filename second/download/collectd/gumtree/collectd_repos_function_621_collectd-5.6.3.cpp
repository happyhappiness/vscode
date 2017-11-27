static jobject ctoj_value_to_number(JNIEnv *jvm_env, /* {{{ */
                                    value_t value, int ds_type) {
  if (ds_type == DS_TYPE_COUNTER)
    return (ctoj_jlong_to_number(jvm_env, (jlong)value.counter));
  else if (ds_type == DS_TYPE_GAUGE)
    return (ctoj_jdouble_to_number(jvm_env, (jdouble)value.gauge));
  if (ds_type == DS_TYPE_DERIVE)
    return (ctoj_jlong_to_number(jvm_env, (jlong)value.derive));
  if (ds_type == DS_TYPE_ABSOLUTE)
    return (ctoj_jlong_to_number(jvm_env, (jlong)value.absolute));
  else
    return (NULL);
}