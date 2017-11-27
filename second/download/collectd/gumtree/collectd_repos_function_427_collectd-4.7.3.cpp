static int cjni_shutdown (void) /* {{{ */
{
  JNIEnv *jvm_env;
  JavaVMAttachArgs args;
  int status;
  size_t i;

  if (jvm == NULL)
    return (0);

  jvm_env = NULL;
  memset (&args, 0, sizeof (args));
  args.version = JNI_VERSION_1_2;

  status = (*jvm)->AttachCurrentThread (jvm, (void *) &jvm_env, &args);
  if (status != 0)
  {
    ERROR ("java plugin: cjni_shutdown: AttachCurrentThread failed with status %i.",
        status);
    return (-1);
  }

  /* Execute all the shutdown functions registered by plugins. */
  cjni_shutdown_plugins (jvm_env);

  /* Release all the global references to callback functions */
  for (i = 0; i < java_callbacks_num; i++)
  {
    if (java_callbacks[i].object != NULL)
    {
      (*jvm_env)->DeleteGlobalRef (jvm_env, java_callbacks[i].object);
      java_callbacks[i].object = NULL;
    }
    sfree (java_callbacks[i].name);
  }
  java_callbacks_num = 0;
  sfree (java_callbacks);

  /* Release all the global references to directly loaded classes. */
  for (i = 0; i < java_classes_list_len; i++)
  {
    if (java_classes_list[i].object != NULL)
    {
      (*jvm_env)->DeleteGlobalRef (jvm_env, java_classes_list[i].object);
      java_classes_list[i].object = NULL;
    }
    sfree (java_classes_list[i].name);
  }
  java_classes_list_len = 0;
  sfree (java_classes_list);

  /* Destroy the JVM */
  DEBUG ("java plugin: Destroying the JVM.");
  (*jvm)->DestroyJavaVM (jvm);
  jvm = NULL;
  jvm_env = NULL;

  pthread_key_delete (jvm_env_key);

  /* Free the JVM argument list */
  for (i = 0; i < jvm_argc; i++)
    sfree (jvm_argv[i]);
  jvm_argc = 0;
  sfree (jvm_argv);

  return (0);
}