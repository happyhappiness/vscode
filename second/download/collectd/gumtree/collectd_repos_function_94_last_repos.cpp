static int fs_info_notify(virDomainPtr domain, virDomainFSInfoPtr fs_info) {
  notification_t notif;
  int ret = 0;

  /* Local struct, just for the purpose of this function. */
  typedef struct nm_str_item_s {
    const char *name;
    const char *value;
  } nm_str_item_t;

  nm_str_item_t fs_dev_alias[fs_info->ndevAlias];
  nm_str_item_t fs_str_items[] = {
      {.name = "mountpoint", .value = fs_info->mountpoint},
      {.name = "name", .value = fs_info->name},
      {.name = "fstype", .value = fs_info->fstype}};

  for (int i = 0; i < fs_info->ndevAlias; ++i) {
    fs_dev_alias[i].name = "devAlias";
    fs_dev_alias[i].value = fs_info->devAlias[i];
  }

  init_notif(&notif, domain, NOTIF_OKAY, "File system information",
             "file_system", NULL);
  NM_ADD_STR_ITEMS(fs_str_items, STATIC_ARRAY_SIZE(fs_str_items));
  NM_ADD_ITEM(plugin_notification_meta_add_unsigned_int, "ndevAlias",
              fs_info->ndevAlias);
  NM_ADD_STR_ITEMS(fs_dev_alias, fs_info->ndevAlias);

  plugin_dispatch_notification(&notif);

cleanup:
  if (notif.meta)
    plugin_notification_meta_free(notif.meta);
  return ret;
}