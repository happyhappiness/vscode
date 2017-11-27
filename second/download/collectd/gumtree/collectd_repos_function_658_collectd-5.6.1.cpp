static JNIEnv *cjni_thread_attach (void) /* {{{ */
{
  cjni_jvm_env_t *cjni_env;
  JNIEnv *jvm_env;

  /* If we're the first thread to access the JVM, we'll have to create it
   * first.. */
  if (jvm == NULL)
  {
    int status;

    status = cjni_create_jvm ();
    if (status != 0)
    {
      ERROR ("java plugin: cjni_thread_attach: cjni_create_jvm failed.");
      return (NULL);
    }
  }
  assert (jvm != NULL);

  cjni_env = pthread_getspecific (jvm_env_key);
  if (cjni_env == NULL)
  {
    /* This pointer is free'd in `cjni_jvm_env_destroy'. */
    cjni_env = calloc (1, sizeof (*cjni_env));
    if (cjni_env == NULL)
    {
      ERROR ("java plugin: cjni_thread_attach: calloc failed.");
      return (NULL);
    }
    cjni_env->reference_counter = 0;
    cjni_env->jvm_env = NULL;

    pthread_setspecific (jvm_env_key, cjni_env);
  }

  if (cjni_env->reference_counter > 0)
  {
    cjni_env->reference_counter++;
    jvm_env = cjni_env->jvm_env;
  }
  else
  {
    int status;
    JavaVMAttachArgs args = { 0 };

    assert (cjni_env->jvm_env == NULL);

    args.version = JNI_VERSION_1_2;

    status = (*jvm)->AttachCurrentThread (jvm, (void *) &jvm_env, (void *) &args);
    if (status != 0)
    {
      ERROR ("java plugin: cjni_thread_attach: AttachCurrentThread failed "
          "with status %i.", status);
      return (NULL);
    }

    cjni_env->reference_counter = 1;
    cjni_env->jvm_env = jvm_env;
  }

  DEBUG ("java plugin: cjni_thread_attach: cjni_env->reference_counter = %i",
      cjni_env->reference_counter);
  assert (jvm_env != NULL);
  return (jvm_env);
}