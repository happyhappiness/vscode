static int cjni_config_load_plugin (oconfig_item_t *ci) /* {{{ */
{
  JNIEnv *jvm_env;
  java_plugin_class_t *class;
  jmethodID constructor_id;
  jobject tmp_object;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("java plugin: `LoadPlugin' needs exactly one string argument.");
    return (-1);
  }

  jvm_env = cjni_thread_attach ();
  if (jvm_env == NULL)
    return (-1);

  class = (java_plugin_class_t *) realloc (java_classes_list,
      (java_classes_list_len + 1) * sizeof (*java_classes_list));
  if (class == NULL)
  {
    ERROR ("java plugin: realloc failed.");
    cjni_thread_detach ();
    return (-1);
  }
  java_classes_list = class;
  class = java_classes_list + java_classes_list_len;

  memset (class, 0, sizeof (*class));
  class->name = strdup (ci->values[0].value.string);
  if (class->name == NULL)
  {
    ERROR ("java plugin: strdup failed.");
    cjni_thread_detach ();
    return (-1);
  }
  class->class = NULL;
  class->object = NULL;

  { /* Replace all dots ('.') with slashes ('/'). Dots are usually used
       thorough the Java community, but (Sun's) `FindClass' and friends need
       slashes. */
    size_t i;
    for (i = 0; class->name[i] != 0; i++)
      if (class->name[i] == '.')
        class->name[i] = '/';
  }

  DEBUG ("java plugin: Loading class %s", class->name);

  class->class = (*jvm_env)->FindClass (jvm_env, class->name);
  if (class->class == NULL)
  {
    ERROR ("java plugin: cjni_config_load_plugin: FindClass (%s) failed.",
        class->name);
    cjni_thread_detach ();
    free (class->name);
    return (-1);
  }

  constructor_id = (*jvm_env)->GetMethodID (jvm_env, class->class,
      "<init>", "()V");
  if (constructor_id == NULL)
  {
    ERROR ("java plugin: cjni_config_load_plugin: "
        "Could not find the constructor for `%s'.",
        class->name);
    cjni_thread_detach ();
    free (class->name);
    return (-1);
  }

  tmp_object = (*jvm_env)->NewObject (jvm_env, class->class,
      constructor_id);
  if (tmp_object != NULL)
    class->object = (*jvm_env)->NewGlobalRef (jvm_env, tmp_object);
  else
    class->object = NULL;
  if (class->object == NULL)
  {
    ERROR ("java plugin: cjni_config_load_plugin: "
        "Could create a new `%s' object.",
        class->name);
    cjni_thread_detach ();
    free (class->name);
    return (-1);
  }

  cjni_thread_detach ();

  java_classes_list_len++;

  return (0);
}