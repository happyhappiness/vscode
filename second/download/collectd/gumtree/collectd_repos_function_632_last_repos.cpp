static int jtoc_value_list(JNIEnv *jvm_env, value_list_t *vl, /* {{{ */
                           jobject object_ptr) {
  jclass class_ptr;
  int status;
  jlong tmp_long;
  const data_set_t *ds;

  class_ptr = (*jvm_env)->GetObjectClass(jvm_env, object_ptr);
  if (class_ptr == NULL) {
    ERROR("java plugin: jtoc_value_list: GetObjectClass failed.");
    return -1;
  }

/* eo == empty okay */
#define SET_STRING(buffer, method, eo)                                         \
  do {                                                                         \
    status = jtoc_string(jvm_env, buffer, sizeof(buffer), eo, class_ptr,       \
                         object_ptr, method);                                  \
    if (status != 0) {                                                         \
      ERROR("java plugin: jtoc_value_list: jtoc_string (%s) failed.", method); \
      return -1;                                                               \
    }                                                                          \
  } while (0)

  SET_STRING(vl->type, "getType", /* empty = */ 0);

  ds = plugin_get_ds(vl->type);
  if (ds == NULL) {
    ERROR("java plugin: jtoc_value_list: Data-set `%s' is not defined. "
          "Please consult the types.db(5) manpage for mor information.",
          vl->type);
    return -1;
  }

  SET_STRING(vl->host, "getHost", /* empty = */ 0);
  SET_STRING(vl->plugin, "getPlugin", /* empty = */ 0);
  SET_STRING(vl->plugin_instance, "getPluginInstance", /* empty = */ 1);
  SET_STRING(vl->type_instance, "getTypeInstance", /* empty = */ 1);

#undef SET_STRING

  status = jtoc_long(jvm_env, &tmp_long, class_ptr, object_ptr, "getTime");
  if (status != 0) {
    ERROR("java plugin: jtoc_value_list: jtoc_long (getTime) failed.");
    return -1;
  }
  /* Java measures time in milliseconds. */
  vl->time = MS_TO_CDTIME_T(tmp_long);

  status = jtoc_long(jvm_env, &tmp_long, class_ptr, object_ptr, "getInterval");
  if (status != 0) {
    ERROR("java plugin: jtoc_value_list: jtoc_long (getInterval) failed.");
    return -1;
  }
  vl->interval = MS_TO_CDTIME_T(tmp_long);

  status = jtoc_values_array(jvm_env, ds, vl, class_ptr, object_ptr);
  if (status != 0) {
    ERROR("java plugin: jtoc_value_list: jtoc_values_array failed.");
    return -1;
  }

  return 0;
}