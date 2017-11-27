static int cjni_init(void) /* {{{ */
{
  JNIEnv *jvm_env;

  if ((config_block == NULL) && (jvm == NULL)) {
    ERROR("java plugin: cjni_init: No configuration block for "
          "the java plugin was found.");
    return (-1);
  }

  if (config_block != NULL) {
    cjni_config_perform(config_block);
    oconfig_free(config_block);
  }

  if (jvm == NULL) {
    ERROR("java plugin: cjni_init: jvm == NULL");
    return (-1);
  }

  jvm_env = cjni_thread_attach();
  if (jvm_env == NULL)
    return (-1);

  cjni_init_plugins(jvm_env);

  cjni_thread_detach();
  return (0);
}