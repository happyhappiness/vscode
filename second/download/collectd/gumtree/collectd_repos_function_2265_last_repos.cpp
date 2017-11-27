static int sigrok_init_driver(struct config_device *cfdev,
                              struct sr_dev_driver *drv) {
  struct sr_config *src;
  GSList *devlist, *drvopts;
  char hwident[512];

  if (sr_driver_init(sr_ctx, drv) != SR_OK)
    /* Error was logged by libsigrok. */
    return -1;

  drvopts = NULL;
  if (cfdev->conn) {
    if (!(src = malloc(sizeof(*src))))
      return -1;
    src->key = SR_CONF_CONN;
    src->data = g_variant_new_string(cfdev->conn);
    drvopts = g_slist_append(drvopts, src);
  }
  if (cfdev->serialcomm) {
    if (!(src = malloc(sizeof(*src))))
      return -1;
    src->key = SR_CONF_SERIALCOMM;
    src->data = g_variant_new_string(cfdev->serialcomm);
    drvopts = g_slist_append(drvopts, src);
  }
  devlist = sr_driver_scan(drv, drvopts);
  g_slist_free_full(drvopts, (GDestroyNotify)sigrok_free_drvopts);
  if (!devlist) {
    /* Not an error, but the user should know about it. */
    WARNING("sigrok plugin: No device found for \"%s\".", cfdev->name);
    return 0;
  }

  if (g_slist_length(devlist) > 1) {
    INFO("sigrok plugin: %d sigrok devices for device entry "
         "\"%s\": must be 1.",
         g_slist_length(devlist), cfdev->name);
    return -1;
  }
  cfdev->sdi = devlist->data;
  g_slist_free(devlist);
  snprintf(hwident, sizeof(hwident), "%s %s %s",
           cfdev->sdi->vendor ? cfdev->sdi->vendor : "",
           cfdev->sdi->model ? cfdev->sdi->model : "",
           cfdev->sdi->version ? cfdev->sdi->version : "");
  INFO("sigrok plugin: Device \"%s\" is a %s", cfdev->name, hwident);

  if (sr_dev_open(cfdev->sdi) != SR_OK)
    return -1;

  if (sr_session_dev_add(cfdev->sdi) != SR_OK)
    return -1;

  return 1;
}