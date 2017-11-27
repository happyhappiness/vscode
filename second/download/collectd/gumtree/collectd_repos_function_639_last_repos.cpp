static jint JNICALL cjni_api_register_read(JNIEnv *jvm_env, /* {{{ */
                                           jobject this, jobject o_name,
                                           jobject o_read) {
  cjni_callback_info_t *cbi;

  cbi = cjni_callback_info_create(jvm_env, o_name, o_read, CB_TYPE_READ);
  if (cbi == NULL)
    return -1;

  DEBUG("java plugin: Registering new read callback: %s", cbi->name);

  plugin_register_complex_read(
      /* group = */ NULL, cbi->name, cjni_read,
      /* interval = */ 0,
      &(user_data_t){
          .data = cbi, .free_func = cjni_callback_info_destroy,
      });

  (*jvm_env)->DeleteLocalRef(jvm_env, o_read);

  return 0;
}