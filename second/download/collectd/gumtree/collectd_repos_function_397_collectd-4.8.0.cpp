static jint JNICALL cjni_api_dispatch_notification (JNIEnv *jvm_env, /* {{{ */
    jobject this, jobject o_notification)
{
  notification_t n;
  int status;

  memset (&n, 0, sizeof (n));
  n.meta = NULL;

  status = jtoc_notification (jvm_env, &n, o_notification);
  if (status != 0)
  {
    ERROR ("java plugin: cjni_api_dispatch_notification: jtoc_notification failed.");
    return (-1);
  }

  status = plugin_dispatch_notification (&n);

  return (status);
}