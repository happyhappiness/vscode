static jobject JNICALL cjni_api_get_ds(JNIEnv *jvm_env, /* {{{ */
                                       jobject this, jobject o_string_type) {
  const char *ds_name;
  const data_set_t *ds;
  jobject o_dataset;

  ds_name = (*jvm_env)->GetStringUTFChars(jvm_env, o_string_type, 0);
  if (ds_name == NULL) {
    ERROR("java plugin: cjni_api_get_ds: GetStringUTFChars failed.");
    return (NULL);
  }

  ds = plugin_get_ds(ds_name);
  DEBUG("java plugin: cjni_api_get_ds: "
        "plugin_get_ds (%s) = %p;",
        ds_name, (void *)ds);

  (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_string_type, ds_name);

  if (ds == NULL)
    return (NULL);

  o_dataset = ctoj_data_set(jvm_env, ds);
  return (o_dataset);
}