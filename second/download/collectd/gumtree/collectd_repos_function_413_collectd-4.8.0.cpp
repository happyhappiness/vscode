static void cjni_jvm_env_destroy (void *args) /* {{{ */
{
  cjni_jvm_env_t *cjni_env;

  if (args == NULL)
    return;

  cjni_env = (cjni_jvm_env_t *) args;

  if (cjni_env->reference_counter > 0)
  {
    ERROR ("java plugin: cjni_jvm_env_destroy: "
        "cjni_env->reference_counter = %i;", cjni_env->reference_counter);
  }

  if (cjni_env->jvm_env != NULL)
  {
    ERROR ("java plugin: cjni_jvm_env_destroy: cjni_env->jvm_env = %p;",
        (void *) cjni_env->jvm_env);
  }

  /* The pointer is allocated in `cjni_thread_attach' */
  free (cjni_env);
}