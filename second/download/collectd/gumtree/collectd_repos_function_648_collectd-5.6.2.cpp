static jint JNICALL cjni_api_register_notification(JNIEnv *jvm_env, /* {{{ */
                                                   jobject this, jobject o_name,
                                                   jobject o_notification) {
  cjni_callback_info_t *cbi;

  cbi = cjni_callback_info_create(jvm_env, o_name, o_notification,
                                  CB_TYPE_NOTIFICATION);
  if (cbi == NULL)
    return (-1);

  DEBUG("java plugin: Registering new notification callback: %s", cbi->name);

  user_data_t ud = {.data = cbi, .free_func = cjni_callback_info_destroy};

  plugin_register_notification(cbi->name, cjni_notification, &ud);

  (*jvm_env)->DeleteLocalRef(jvm_env, o_notification);

  return (0);
}