static int cjni_callback_register (JNIEnv *jvm_env, /* {{{ */
    jobject o_name, jobject o_callback, int type)
{
  cjni_callback_info_t *cbi;
  cjni_callback_info_t *tmp;
#if COLLECT_DEBUG
  const char *type_str;
#endif

  cbi = cjni_callback_info_create (jvm_env, o_name, o_callback, type);
  if (cbi == NULL)
    return (-1);

#if COLLECT_DEBUG
  switch (type)
  {
    case CB_TYPE_CONFIG:
      type_str = "config";
      break;

    case CB_TYPE_INIT:
      type_str = "init";
      break;

    case CB_TYPE_SHUTDOWN:
      type_str = "shutdown";
      break;

    case CB_TYPE_MATCH:
      type_str = "match";
      break;

    case CB_TYPE_TARGET:
      type_str = "target";
      break;

    default:
      type_str = "<unknown>";
  }
  DEBUG ("java plugin: Registering new %s callback: %s",
      type_str, cbi->name);
#endif

  pthread_mutex_lock (&java_callbacks_lock);

  tmp = (cjni_callback_info_t *) realloc (java_callbacks,
      (java_callbacks_num + 1) * sizeof (*java_callbacks));
  if (tmp == NULL)
  {
    pthread_mutex_unlock (&java_callbacks_lock);
    ERROR ("java plugin: cjni_callback_register: realloc failed.");

    (*jvm_env)->DeleteGlobalRef (jvm_env, cbi->object);
    free (cbi);

    return (-1);
  }
  java_callbacks = tmp;
  java_callbacks[java_callbacks_num] = *cbi;
  java_callbacks_num++;

  pthread_mutex_unlock (&java_callbacks_lock);

  free (cbi);
  return (0);
}