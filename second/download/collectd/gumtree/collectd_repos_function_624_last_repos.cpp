static jobject ctoj_value_list(JNIEnv *jvm_env, /* {{{ */
                               const data_set_t *ds, const value_list_t *vl) {
  jclass c_valuelist;
  jmethodID m_valuelist_constructor;
  jobject o_valuelist;
  int status;

  /* First, create a new ValueList instance..
   * Look up the class.. */
  c_valuelist = (*jvm_env)->FindClass(jvm_env, "org/collectd/api/ValueList");
  if (c_valuelist == NULL) {
    ERROR("java plugin: ctoj_value_list: "
          "FindClass (org/collectd/api/ValueList) failed.");
    return NULL;
  }

  /* Lookup the `ValueList ()' constructor. */
  m_valuelist_constructor =
      (*jvm_env)->GetMethodID(jvm_env, c_valuelist, "<init>", "()V");
  if (m_valuelist_constructor == NULL) {
    ERROR("java plugin: ctoj_value_list: Cannot find the "
          "`ValueList ()' constructor.");
    return NULL;
  }

  /* Create a new instance. */
  o_valuelist =
      (*jvm_env)->NewObject(jvm_env, c_valuelist, m_valuelist_constructor);
  if (o_valuelist == NULL) {
    ERROR("java plugin: ctoj_value_list: Creating a new ValueList instance "
          "failed.");
    return NULL;
  }

  status = ctoj_value_list_add_data_set(jvm_env, c_valuelist, o_valuelist, ds);
  if (status != 0) {
    ERROR("java plugin: ctoj_value_list: "
          "ctoj_value_list_add_data_set failed.");
    (*jvm_env)->DeleteLocalRef(jvm_env, o_valuelist);
    return NULL;
  }

/* Set the strings.. */
#define SET_STRING(str, method_name)                                           \
  do {                                                                         \
    status = ctoj_string(jvm_env, str, c_valuelist, o_valuelist, method_name); \
    if (status != 0) {                                                         \
      ERROR("java plugin: ctoj_value_list: ctoj_string (%s) failed.",          \
            method_name);                                                      \
      (*jvm_env)->DeleteLocalRef(jvm_env, o_valuelist);                        \
      return NULL;                                                             \
    }                                                                          \
  } while (0)

  SET_STRING(vl->host, "setHost");
  SET_STRING(vl->plugin, "setPlugin");
  SET_STRING(vl->plugin_instance, "setPluginInstance");
  SET_STRING(vl->type, "setType");
  SET_STRING(vl->type_instance, "setTypeInstance");

#undef SET_STRING

  /* Set the `time' member. Java stores time in milliseconds. */
  status = ctoj_long(jvm_env, (jlong)CDTIME_T_TO_MS(vl->time), c_valuelist,
                     o_valuelist, "setTime");
  if (status != 0) {
    ERROR("java plugin: ctoj_value_list: ctoj_long (setTime) failed.");
    (*jvm_env)->DeleteLocalRef(jvm_env, o_valuelist);
    return NULL;
  }

  /* Set the `interval' member.. */
  status = ctoj_long(jvm_env, (jlong)CDTIME_T_TO_MS(vl->interval), c_valuelist,
                     o_valuelist, "setInterval");
  if (status != 0) {
    ERROR("java plugin: ctoj_value_list: ctoj_long (setInterval) failed.");
    (*jvm_env)->DeleteLocalRef(jvm_env, o_valuelist);
    return NULL;
  }

  for (size_t i = 0; i < vl->values_len; i++) {
    status = ctoj_value_list_add_value(jvm_env, vl->values[i], ds->ds[i].type,
                                       c_valuelist, o_valuelist);
    if (status != 0) {
      ERROR("java plugin: ctoj_value_list: "
            "ctoj_value_list_add_value failed.");
      (*jvm_env)->DeleteLocalRef(jvm_env, o_valuelist);
      return NULL;
    }
  }

  return o_valuelist;
}