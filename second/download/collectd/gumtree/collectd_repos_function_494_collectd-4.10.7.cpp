static int cjni_shutdown_plugins (JNIEnv *jvm_env) /* {{{ */
{
  int status;
  size_t i;

  for (i = 0; i < java_callbacks_num; i++)
  {
    if (java_callbacks[i].type != CB_TYPE_SHUTDOWN)
      continue;

    DEBUG ("java plugin: Shutting down %s", java_callbacks[i].name);

    status = (*jvm_env)->CallIntMethod (jvm_env,
        java_callbacks[i].object, java_callbacks[i].method);
    if (status != 0)
    {
      ERROR ("java plugin: Shutting down `%s' failed with status %i. ",
          java_callbacks[i].name, status);
    }
  }

  return (0);
}