static int cjni_write (const data_set_t *ds, const value_list_t *vl, /* {{{ */
    user_data_t *ud)
{
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi;
  jobject vl_java;
  int ret_status;

  if (jvm == NULL)
  {
    ERROR ("java plugin: cjni_write: jvm == NULL");
    return (-1);
  }

  if ((ud == NULL) || (ud->data == NULL))
  {
    ERROR ("java plugin: cjni_write: Invalid user data.");
    return (-1);
  }

  jvm_env = cjni_thread_attach ();
  if (jvm_env == NULL)
    return (-1);

  cbi = (cjni_callback_info_t *) ud->data;

  vl_java = ctoj_value_list (jvm_env, ds, vl);
  if (vl_java == NULL)
  {
    ERROR ("java plugin: cjni_write: ctoj_value_list failed.");
    cjni_thread_detach ();
    return (-1);
  }

  ret_status = (*jvm_env)->CallIntMethod (jvm_env,
      cbi->object, cbi->method, vl_java);

  (*jvm_env)->DeleteLocalRef (jvm_env, vl_java);

  cjni_thread_detach ();
  return (ret_status);
}