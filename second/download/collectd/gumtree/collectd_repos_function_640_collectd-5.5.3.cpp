static cjni_callback_info_t *cjni_callback_info_create (JNIEnv *jvm_env, /* {{{ */
    jobject o_name, jobject o_callback, int type)
{
  const char *c_name;
  cjni_callback_info_t *cbi;
  const char *method_name;
  const char *method_signature;

  switch (type)
  {
    case CB_TYPE_CONFIG:
      method_name = "config";
      method_signature = "(Lorg/collectd/api/OConfigItem;)I";
      break;

    case CB_TYPE_INIT:
      method_name = "init";
      method_signature = "()I";
      break;

    case CB_TYPE_READ:
      method_name = "read";
      method_signature = "()I";
      break;

    case CB_TYPE_WRITE:
      method_name = "write";
      method_signature = "(Lorg/collectd/api/ValueList;)I";
      break;

    case CB_TYPE_FLUSH:
      method_name = "flush";
      method_signature = "(Ljava/lang/Number;Ljava/lang/String;)I";
      break;

    case CB_TYPE_SHUTDOWN:
      method_name = "shutdown";
      method_signature = "()I";
      break;

    case CB_TYPE_LOG:
      method_name = "log";
      method_signature = "(ILjava/lang/String;)V";
      break;

    case CB_TYPE_NOTIFICATION:
      method_name = "notification";
      method_signature = "(Lorg/collectd/api/Notification;)I";
      break;

    case CB_TYPE_MATCH:
      method_name = "createMatch";
      method_signature = "(Lorg/collectd/api/OConfigItem;)"
        "Lorg/collectd/api/CollectdMatchInterface;";
      break;

    case CB_TYPE_TARGET:
      method_name = "createTarget";
      method_signature = "(Lorg/collectd/api/OConfigItem;)"
        "Lorg/collectd/api/CollectdTargetInterface;";
      break;

    default:
      ERROR ("java plugin: cjni_callback_info_create: Unknown type: %#x",
          type);
      return (NULL);
  }

  c_name = (*jvm_env)->GetStringUTFChars (jvm_env, o_name, 0);
  if (c_name == NULL)
  {
    ERROR ("java plugin: cjni_callback_info_create: "
        "GetStringUTFChars failed.");
    return (NULL);
  }

  cbi = (cjni_callback_info_t *) malloc (sizeof (*cbi));
  if (cbi == NULL)
  {
    ERROR ("java plugin: cjni_callback_info_create: malloc failed.");
    (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_name, c_name);
    return (NULL);
  }
  memset (cbi, 0, sizeof (*cbi));
  cbi->type = type;

  cbi->name = strdup (c_name);
  if (cbi->name == NULL)
  {
    pthread_mutex_unlock (&java_callbacks_lock);
    ERROR ("java plugin: cjni_callback_info_create: strdup failed.");
    (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_name, c_name);
    sfree (cbi);
    return (NULL);
  }

  (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_name, c_name);

  cbi->object = (*jvm_env)->NewGlobalRef (jvm_env, o_callback);
  if (cbi->object == NULL)
  {
    ERROR ("java plugin: cjni_callback_info_create: NewGlobalRef failed.");
    sfree (cbi->name);
    sfree (cbi);
    return (NULL);
  }

  cbi->class  = (*jvm_env)->GetObjectClass (jvm_env, cbi->object);
  if (cbi->class == NULL)
  {
    ERROR ("java plugin: cjni_callback_info_create: GetObjectClass failed.");
    (*jvm_env)->DeleteGlobalRef (jvm_env, cbi->object);
    sfree (cbi->name);
    sfree (cbi);
    return (NULL);
  }

  cbi->method = (*jvm_env)->GetMethodID (jvm_env, cbi->class,
      method_name, method_signature);
  if (cbi->method == NULL)
  {
    ERROR ("java plugin: cjni_callback_info_create: "
        "Cannot find the `%s' method with signature `%s'.",
        method_name, method_signature);
    (*jvm_env)->DeleteGlobalRef (jvm_env, cbi->object);
    sfree (cbi->name);
    sfree (cbi);
    return (NULL);
  }

  return (cbi);
}