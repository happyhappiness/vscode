static int cjni_config_plugin_block (oconfig_item_t *ci) /* {{{ */
{
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi;
  jobject o_ocitem;
  const char *name;
  int status;
  size_t i;

  jclass class;
  jmethodID method;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("java plugin: `Plugin' blocks "
        "need exactly one string argument.");
    return (-1);
  }

  name = ci->values[0].value.string;

  cbi = NULL;
  for (i = 0; i < java_callbacks_num; i++)
  {
    if (java_callbacks[i].type != CB_TYPE_CONFIG)
      continue;

    if (strcmp (name, java_callbacks[i].name) != 0)
      continue;

    cbi = java_callbacks + i;
    break;
  }

  if (cbi == NULL)
  {
    NOTICE ("java plugin: Configuration block for `%s' found, but no such "
        "configuration callback has been registered. Please make sure, the "
        "`LoadPlugin' lines precede the `Plugin' blocks.",
        name);
    return (0);
  }

  DEBUG ("java plugin: Configuring %s", name);

  jvm_env = cjni_thread_attach ();
  if (jvm_env == NULL)
    return (-1);

  o_ocitem = ctoj_oconfig_item (jvm_env, ci);
  if (o_ocitem == NULL)
  {
    ERROR ("java plugin: cjni_config_plugin_block: ctoj_oconfig_item failed.");
    cjni_thread_detach ();
    return (-1);
  }

  class = (*jvm_env)->GetObjectClass (jvm_env, cbi->object);
  method = (*jvm_env)->GetMethodID (jvm_env, class,
      "config", "(Lorg/collectd/api/OConfigItem;)I");

  status = (*jvm_env)->CallIntMethod (jvm_env,
      cbi->object, method, o_ocitem);

  (*jvm_env)->DeleteLocalRef (jvm_env, o_ocitem);
  cjni_thread_detach ();
  return (0);
}