static int cjni_create_jvm(void) /* {{{ */
{
  JNIEnv *jvm_env;
  JavaVMInitArgs vm_args = {0};
  JavaVMOption vm_options[jvm_argc];

  int status;

  if (jvm != NULL)
    return (0);

  status = pthread_key_create(&jvm_env_key, cjni_jvm_env_destroy);
  if (status != 0) {
    ERROR("java plugin: cjni_create_jvm: pthread_key_create failed "
          "with status %i.",
          status);
    return (-1);
  }

  jvm_env = NULL;

  vm_args.version = JNI_VERSION_1_2;
  vm_args.options = vm_options;
  vm_args.nOptions = (jint)jvm_argc;

  for (size_t i = 0; i < jvm_argc; i++) {
    DEBUG("java plugin: cjni_create_jvm: jvm_argv[%zu] = %s", i, jvm_argv[i]);
    vm_args.options[i].optionString = jvm_argv[i];
  }

  status = JNI_CreateJavaVM(&jvm, (void *)&jvm_env, (void *)&vm_args);
  if (status != 0) {
    ERROR("java plugin: cjni_create_jvm: "
          "JNI_CreateJavaVM failed with status %i.",
          status);
    return (-1);
  }
  assert(jvm != NULL);
  assert(jvm_env != NULL);

  /* Call RegisterNatives */
  status = cjni_init_native(jvm_env);
  if (status != 0) {
    ERROR("java plugin: cjni_create_jvm: cjni_init_native failed.");
    return (-1);
  }

  DEBUG("java plugin: The JVM has been created.");
  return (0);
}