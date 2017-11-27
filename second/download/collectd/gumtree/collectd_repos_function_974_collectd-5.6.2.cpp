static int pplugin_dispatch_notification(pTHX_ HV *notif) {
  notification_t n = {0};

  int ret;

  if (NULL == notif)
    return -1;

  if (0 != hv2notification(aTHX_ notif, &n))
    return -1;

  ret = plugin_dispatch_notification(&n);
  plugin_notification_meta_free(n.meta);
  return ret;
}