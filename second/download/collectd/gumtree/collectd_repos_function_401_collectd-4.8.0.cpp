static jint JNICALL cjni_api_register_read (JNIEnv *jvm_env, /* {{{ */
    jobject this, jobject o_name, jobject o_read)
{
  user_data_t ud;
  cjni_callback_info_t *cbi;

  cbi = cjni_callback_info_create (jvm_env, o_name, o_read, CB_TYPE_READ);
  if (cbi == NULL)
    return (-1);

  DEBUG ("java plugin: Registering new read callback: %s", cbi->name);

  memset (&ud, 0, sizeof (ud));
  ud.data = (void *) cbi;
  ud.free_func = cjni_callback_info_destroy;

  plugin_register_complex_read (cbi->name, cjni_read,
      /* interval = */ NULL, &ud);

  (*jvm_env)->DeleteLocalRef (jvm_env, o_read);

  return (0);
}