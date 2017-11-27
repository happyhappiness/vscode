static int cjni_thread_detach (void) /* {{{ */
{
  cjni_jvm_env_t *cjni_env;
  int status;

  cjni_env = pthread_getspecific (jvm_env_key);
  if (cjni_env == NULL)
  {
    ERROR ("java plugin: cjni_thread_detach: pthread_getspecific failed.");
    return (-1);
  }

  assert (cjni_env->reference_counter > 0);
  assert (cjni_env->jvm_env != NULL);

  cjni_env->reference_counter--;
  DEBUG ("java plugin: cjni_thread_detach: cjni_env->reference_counter = %i",
      cjni_env->reference_counter);

  if (cjni_env->reference_counter > 0)
    return (0);

  status = (*jvm)->DetachCurrentThread (jvm);
  if (status != 0)
  {
    ERROR ("java plugin: cjni_thread_detach: DetachCurrentThread failed "
        "with status %i.", status);
  }

  cjni_env->reference_counter = 0;
  cjni_env->jvm_env = NULL;

  return (0);
}