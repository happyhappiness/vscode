static int cjni_flush (cdtime_t timeout, const char *identifier, /* {{{ */
    user_data_t *ud)
{
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi;
  jobject o_timeout;
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

  o_timeout = ctoj_jdouble_to_number (jvm_env,
      (jdouble) CDTIME_T_TO_DOUBLE (timeout));
  if (o_timeout == NULL)
  {
    ERROR ("java plugin: cjni_flush: Converting double "
        "to Number object failed.");
    return (-1);
  }

  o_identifier = NULL;
  if (identifier != NULL)
  {
    o_identifier = (*jvm_env)->NewStringUTF (jvm_env, identifier);
    if (o_identifier == NULL)
    {
      (*jvm_env)->DeleteLocalRef (jvm_env, o_timeout);
      ERROR ("java plugin: cjni_flush: NewStringUTF failed.");
      return (-1);
    }
  }

  ret_status = (*jvm_env)->CallIntMethod (jvm_env,
      cbi->object, cbi->method, o_timeout, o_identifier);

  (*jvm_env)->DeleteLocalRef (jvm_env, o_identifier);
  (*jvm_env)->DeleteLocalRef (jvm_env, o_timeout);

  status = cjni_thread_detach ();
  if (status != 0)
  {
    ERROR ("java plugin: cjni_flush: cjni_thread_detach failed.");
    return (-1);
  }

  return (ret_status);
}