static jint JNICALL cjni_api_register_write(JNIEnv *jvm_env, /* {{{ */
                                            jobject this, jobject o_name,
                                            jobject o_write) {
  cjni_callback_info_t *cbi;

  cbi = cjni_callback_info_create(jvm_env, o_name, o_write, CB_TYPE_WRITE);
  if (cbi == NULL)
    return (-1);

  DEBUG("java plugin: Registering new write callback: %s", cbi->name);

  user_data_t ud = {.data = cbi, .free_func = cjni_callback_info_destroy};

  plugin_register_write(cbi->name, cjni_write, &ud);

  (*jvm_env)->DeleteLocalRef(jvm_env, o_write);

  return (0);
}