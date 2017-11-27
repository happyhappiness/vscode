static jint JNICALL cjni_api_register_flush(JNIEnv *jvm_env, /* {{{ */
                                            jobject this, jobject o_name,
                                            jobject o_flush) {
  cjni_callback_info_t *cbi;

  cbi = cjni_callback_info_create(jvm_env, o_name, o_flush, CB_TYPE_FLUSH);
  if (cbi == NULL)
    return (-1);

  DEBUG("java plugin: Registering new flush callback: %s", cbi->name);

  user_data_t ud = {.data = cbi, .free_func = cjni_callback_info_destroy};

  plugin_register_flush(cbi->name, cjni_flush, &ud);

  (*jvm_env)->DeleteLocalRef(jvm_env, o_flush);

  return (0);
}