static int cjni_init_plugins(JNIEnv *jvm_env) /* {{{ */
{
  int status;

  for (size_t i = 0; i < java_callbacks_num; i++) {
    if (java_callbacks[i].type != CB_TYPE_INIT)
      continue;

    DEBUG("java plugin: Initializing %s", java_callbacks[i].name);

    status = (*jvm_env)->CallIntMethod(jvm_env, java_callbacks[i].object,
                                       java_callbacks[i].method);
    if (status != 0) {
      ERROR("java plugin: Initializing `%s' failed with status %i. "
            "Removing read function.",
            java_callbacks[i].name, status);
      plugin_unregister_read(java_callbacks[i].name);
    }
  }

  return 0;
}