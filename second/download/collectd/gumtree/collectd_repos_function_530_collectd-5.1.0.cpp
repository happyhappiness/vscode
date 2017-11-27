static int cjni_read (user_data_t *ud) /* {{{ */
{
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi;
  int status;
  int ret_status;

  if (jvm == NULL)
  {
    ERROR ("java plugin: cjni_read: jvm == NULL");
    return (-1);
  }

  if ((ud == NULL) || (ud->data == NULL))
  {
    ERROR ("java plugin: cjni_read: Invalid user data.");
    return (-1);
  }

  jvm_env = cjni_thread_attach ();
  if (jvm_env == NULL)
    return (-1);

  cbi = (cjni_callback_info_t *) ud->data;

  ret_status = (*jvm_env)->CallIntMethod (jvm_env, cbi->object,
      cbi->method);

  status = cjni_thread_detach ();
  if (status != 0)
  {
    ERROR ("java plugin: cjni_read: cjni_thread_detach failed.");
    return (-1);
  }

  return (ret_status);
}