static int cjni_flush (int timeout, const char *identifier, /* {{{ */
    user_data_t *ud)
{
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi;
  jobject o_identifier;
  int status;
  int ret_status;

  if (jvm == NULL)
  {
    ERROR ("java plugin: cjni_flush: jvm == NULL");
    return (-1);
  }

  if ((ud == NULL) || (ud->data == NULL))
  {
    ERROR ("java plugin: cjni_flush: Invalid user data.");
    return (-1);
  }

  jvm_env = cjni_thread_attach ();
  if (jvm_env == NULL)
    return (-1);

  cbi = (cjni_callback_info_t *) ud->data;

  o_identifier = NULL;
  if (identifier != NULL)
  {
    o_identifier = (*jvm_env)->NewStringUTF (jvm_env, identifier);
    if (o_identifier == NULL)
    {
      ERROR ("java plugin: cjni_flush: NewStringUTF failed.");
      return (-1);
    }
  }

  ret_status = (*jvm_env)->CallIntMethod (jvm_env,
      cbi->object, cbi->method, (jint) timeout, o_identifier);

  (*jvm_env)->DeleteLocalRef (jvm_env, o_identifier);

  status = cjni_thread_detach ();
  if (status != 0)
  {
    ERROR ("java plugin: cjni_flush: cjni_thread_detach failed.");
    return (-1);
  }

  return (ret_status);
}