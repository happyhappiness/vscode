static jobject ctoj_notification(JNIEnv *jvm_env, /* {{{ */
                                 const notification_t *n) {
  jclass c_notification;
  jmethodID m_constructor;
  jobject o_notification;
  int status;

  /* First, create a new Notification instance..
   * Look up the class.. */
  c_notification =
      (*jvm_env)->FindClass(jvm_env, "org/collectd/api/Notification");
  if (c_notification == NULL) {
    ERROR("java plugin: ctoj_notification: "
          "FindClass (org/collectd/api/Notification) failed.");
    return (NULL);
  }

  /* Lookup the `Notification ()' constructor. */
  m_constructor =
      (*jvm_env)->GetMethodID(jvm_env, c_notification, "<init>", "()V");
  if (m_constructor == NULL) {
    ERROR("java plugin: ctoj_notification: Cannot find the "
          "`Notification ()' constructor.");
    return (NULL);
  }

  /* Create a new instance. */
  o_notification =
      (*jvm_env)->NewObject(jvm_env, c_notification, m_constructor);
  if (o_notification == NULL) {
    ERROR("java plugin: ctoj_notification: Creating a new Notification "
          "instance failed.");
    return (NULL);
  }

/* Set the strings.. */
#define SET_STRING(str, method_name)                                           \
  do {                                                                         \
    status = ctoj_string(jvm_env, str, c_notification, o_notification,         \
                         method_name);                                         \
    if (status != 0) {                                                         \
      ERROR("java plugin: ctoj_notification: ctoj_string (%s) failed.",        \
            method_name);                                                      \
      (*jvm_env)->DeleteLocalRef(jvm_env, o_notification);                     \
      return (NULL);                                                           \
    }                                                                          \
  } while (0)

  SET_STRING(n->host, "setHost");
  SET_STRING(n->plugin, "setPlugin");
  SET_STRING(n->plugin_instance, "setPluginInstance");
  SET_STRING(n->type, "setType");
  SET_STRING(n->type_instance, "setTypeInstance");
  SET_STRING(n->message, "setMessage");

#undef SET_STRING

  /* Set the `time' member. Java stores time in milliseconds. */
  status = ctoj_long(jvm_env, (jlong)CDTIME_T_TO_MS(n->time), c_notification,
                     o_notification, "setTime");
  if (status != 0) {
    ERROR("java plugin: ctoj_notification: ctoj_long (setTime) failed.");
    (*jvm_env)->DeleteLocalRef(jvm_env, o_notification);
    return (NULL);
  }

  /* Set the `severity' member.. */
  status = ctoj_int(jvm_env, (jint)n->severity, c_notification, o_notification,
                    "setSeverity");
  if (status != 0) {
    ERROR("java plugin: ctoj_notification: ctoj_int (setSeverity) failed.");
    (*jvm_env)->DeleteLocalRef(jvm_env, o_notification);
    return (NULL);
  }

  return (o_notification);
}