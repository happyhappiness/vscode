static int jtoc_notification (JNIEnv *jvm_env, notification_t *n, /* {{{ */
    jobject object_ptr)
{
  jclass class_ptr;
  int status;
  jlong tmp_long;
  jint tmp_int;

  class_ptr = (*jvm_env)->GetObjectClass (jvm_env, object_ptr);
  if (class_ptr == NULL)
  {
    ERROR ("java plugin: jtoc_notification: GetObjectClass failed.");
    return (-1);
  }

  /* eo == empty okay */
#define SET_STRING(buffer,method, eo) do { \
  status = jtoc_string (jvm_env, buffer, sizeof (buffer), eo, \
      class_ptr, object_ptr, method); \
  if (status != 0) { \
    ERROR ("java plugin: jtoc_notification: jtoc_string (%s) failed.", \
        method); \
    return (-1); \
  } } while (0)

  SET_STRING (n->host,            "getHost",           /* empty = */ 1);
  SET_STRING (n->plugin,          "getPlugin",         /* empty = */ 1);
  SET_STRING (n->plugin_instance, "getPluginInstance", /* empty = */ 1);
  SET_STRING (n->type,            "getType",           /* empty = */ 1);
  SET_STRING (n->type_instance,   "getTypeInstance",   /* empty = */ 1);
  SET_STRING (n->message,         "getMessage",        /* empty = */ 0);

#undef SET_STRING

  status = jtoc_long (jvm_env, &tmp_long, class_ptr, object_ptr, "getTime");
  if (status != 0)
  {
    ERROR ("java plugin: jtoc_notification: jtoc_long (getTime) failed.");
    return (-1);
  }
  /* Java measures time in milliseconds. */
  n->time = MS_TO_CDTIME_T(tmp_long);

  status = jtoc_int (jvm_env, &tmp_int,
      class_ptr, object_ptr, "getSeverity");
  if (status != 0)
  {
    ERROR ("java plugin: jtoc_notification: jtoc_int (getSeverity) failed.");
    return (-1);
  }
  n->severity = (int) tmp_int;

  return (0);
}