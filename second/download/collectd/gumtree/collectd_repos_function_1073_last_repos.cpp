static void mcelog_dispatch_notification(notification_t *n) {
  if (!n) {
    ERROR(MCELOG_PLUGIN ": %s: NULL pointer", __FUNCTION__);
    return;
  }

  sstrncpy(n->host, hostname_g, sizeof(n->host));
  sstrncpy(n->type, "gauge", sizeof(n->type));
  plugin_dispatch_notification(n);
  if (n->meta)
    plugin_notification_meta_free(n->meta);
}