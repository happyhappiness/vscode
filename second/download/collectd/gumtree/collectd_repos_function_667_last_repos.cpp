static int cjni_notification(const notification_t *n, /* {{{ */
                             user_data_t *ud) {
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi;
  jobject o_notification;
  int ret_status;

  if (jvm == NULL) {
    ERROR("java plugin: cjni_read: jvm == NULL");
    return -1;
  }

  if ((ud == NULL) || (ud->data == NULL)) {
    ERROR("java plugin: cjni_read: Invalid user data.");
    return -1;
  }

  jvm_env = cjni_thread_attach();
  if (jvm_env == NULL)
    return -1;

  cbi = (cjni_callback_info_t *)ud->data;

  o_notification = ctoj_notification(jvm_env, n);
  if (o_notification == NULL) {
    ERROR("java plugin: cjni_notification: ctoj_notification failed.");
    cjni_thread_detach();
    return -1;
  }

  ret_status = (*jvm_env)->CallIntMethod(jvm_env, cbi->object, cbi->method,
                                         o_notification);

  (*jvm_env)->DeleteLocalRef(jvm_env, o_notification);

  cjni_thread_detach();
  return ret_status;
}