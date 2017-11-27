static int cjni_read(user_data_t *ud) /* {{{ */
{
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi;
  int ret_status;

  if (jvm == NULL) {
    ERROR("java plugin: cjni_read: jvm == NULL");
    return (-1);
  }

  if ((ud == NULL) || (ud->data == NULL)) {
    ERROR("java plugin: cjni_read: Invalid user data.");
    return (-1);
  }

  jvm_env = cjni_thread_attach();
  if (jvm_env == NULL)
    return (-1);

  cbi = (cjni_callback_info_t *)ud->data;

  ret_status = (*jvm_env)->CallIntMethod(jvm_env, cbi->object, cbi->method);

  cjni_thread_detach();
  return (ret_status);
}