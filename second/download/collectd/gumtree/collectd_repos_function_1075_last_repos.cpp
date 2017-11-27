static int mcelog_dispatch_mem_notifications(const mcelog_memory_rec_t *mr) {
  notification_t n = {.severity = NOTIF_WARNING,
                      .time = cdtime(),
                      .plugin = MCELOG_PLUGIN,
                      .type = "errors"};

  int dispatch_corrected_notifs = 0, dispatch_uncorrected_notifs = 0;

  if (mr == NULL)
    return -1;

  llentry_t *dimm = mcelog_dimm(mr, g_mcelog_config.dimms_list);
  if (dimm == NULL) {
    ERROR(MCELOG_PLUGIN
          ": Error adding/getting dimm memory item to/from cache");
    return -1;
  }
  mcelog_memory_rec_t *mr_old = dimm->value;
  if (!g_mcelog_config.persist) {

    if (mr_old->corrected_err_total != mr->corrected_err_total ||
        mr_old->corrected_err_timed != mr->corrected_err_timed)
      dispatch_corrected_notifs = 1;

    if (mr_old->uncorrected_err_total != mr->uncorrected_err_total ||
        mr_old->uncorrected_err_timed != mr->uncorrected_err_timed)
      dispatch_uncorrected_notifs = 1;

    if (!dispatch_corrected_notifs && !dispatch_uncorrected_notifs) {
      DEBUG("%s: No new notifications to dispatch", MCELOG_PLUGIN);
      return 0;
    }
  } else {
    dispatch_corrected_notifs = 1;
    dispatch_uncorrected_notifs = 1;
  }

  sstrncpy(n.host, hostname_g, sizeof(n.host));

  if (mr->dimm_name[0] != '\0')
    snprintf(n.plugin_instance, sizeof(n.plugin_instance), "%s_%s",
             mr->location, mr->dimm_name);
  else
    sstrncpy(n.plugin_instance, mr->location, sizeof(n.plugin_instance));

  if (dispatch_corrected_notifs &&
      (mr->corrected_err_total > 0 || mr->corrected_err_timed > 0)) {
    /* Corrected Error Notifications */
    plugin_notification_meta_add_signed_int(&n, MCELOG_CORRECTED_ERR,
                                            mr->corrected_err_total);
    plugin_notification_meta_add_signed_int(&n, MCELOG_CORRECTED_ERR_TIMED,
                                            mr->corrected_err_timed);
    snprintf(n.message, sizeof(n.message), MCELOG_CORRECTED_ERR);
    sstrncpy(n.type_instance, MCELOG_CORRECTED_ERR_TYPE_INS,
             sizeof(n.type_instance));
    plugin_dispatch_notification(&n);
    if (n.meta)
      plugin_notification_meta_free(n.meta);
    n.meta = NULL;
  }

  if (dispatch_uncorrected_notifs &&
      (mr->uncorrected_err_total > 0 || mr->uncorrected_err_timed > 0)) {
    /* Uncorrected Error Notifications */
    plugin_notification_meta_add_signed_int(&n, MCELOG_UNCORRECTED_ERR,
                                            mr->uncorrected_err_total);
    plugin_notification_meta_add_signed_int(&n, MCELOG_UNCORRECTED_ERR_TIMED,
                                            mr->uncorrected_err_timed);
    snprintf(n.message, sizeof(n.message), MCELOG_UNCORRECTED_ERR);
    sstrncpy(n.type_instance, MCELOG_UNCORRECTED_ERR_TYPE_INS,
             sizeof(n.type_instance));
    n.severity = NOTIF_FAILURE;
    plugin_dispatch_notification(&n);
    if (n.meta)
      plugin_notification_meta_free(n.meta);
    n.meta = NULL;
  }

  return 0;
}