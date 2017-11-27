static void cjni_callback_info_destroy (void *arg) /* {{{ */
{
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi;

  DEBUG ("java plugin: cjni_callback_info_destroy (arg = %p);", arg);

  cbi = (cjni_callback_info_t *) arg;

  /* This condition can occur when shutting down. */
  if (jvm == NULL)
  {
    sfree (cbi);
    return;
  }

  if (arg == NULL)
    return;

  jvm_env = cjni_thread_attach ();
  if (jvm_env == NULL)
  {
    ERROR ("java plugin: cjni_callback_info_destroy: cjni_thread_attach failed.");
    return;
  }

  (*jvm_env)->DeleteGlobalRef (jvm_env, cbi->object);

  cbi->method = NULL;
  cbi->object = NULL;
  cbi->class  = NULL;
  free (cbi);

  cjni_thread_detach ();
}