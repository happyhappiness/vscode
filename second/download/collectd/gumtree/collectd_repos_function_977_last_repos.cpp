static int hv2notification(pTHX_ HV *hash, notification_t *n) {
  SV **tmp = NULL;

  if ((NULL == hash) || (NULL == n))
    return -1;

  if (NULL != (tmp = hv_fetch(hash, "severity", 8, 0)))
    n->severity = SvIV(*tmp);
  else
    n->severity = NOTIF_FAILURE;

  if (NULL != (tmp = hv_fetch(hash, "time", 4, 0))) {
    double t = SvNV(*tmp);
    n->time = DOUBLE_TO_CDTIME_T(t);
  } else
    n->time = cdtime();

  if (NULL != (tmp = hv_fetch(hash, "message", 7, 0)))
    sstrncpy(n->message, SvPV_nolen(*tmp), sizeof(n->message));

  if (NULL != (tmp = hv_fetch(hash, "host", 4, 0)))
    sstrncpy(n->host, SvPV_nolen(*tmp), sizeof(n->host));
  else
    sstrncpy(n->host, hostname_g, sizeof(n->host));

  if (NULL != (tmp = hv_fetch(hash, "plugin", 6, 0)))
    sstrncpy(n->plugin, SvPV_nolen(*tmp), sizeof(n->plugin));

  if (NULL != (tmp = hv_fetch(hash, "plugin_instance", 15, 0)))
    sstrncpy(n->plugin_instance, SvPV_nolen(*tmp), sizeof(n->plugin_instance));

  if (NULL != (tmp = hv_fetch(hash, "type", 4, 0)))
    sstrncpy(n->type, SvPV_nolen(*tmp), sizeof(n->type));

  if (NULL != (tmp = hv_fetch(hash, "type_instance", 13, 0)))
    sstrncpy(n->type_instance, SvPV_nolen(*tmp), sizeof(n->type_instance));

  n->meta = NULL;
  while (NULL != (tmp = hv_fetch(hash, "meta", 4, 0))) {
    if (!(SvROK(*tmp) && (SVt_PVAV == SvTYPE(SvRV(*tmp))))) {
      log_warn("hv2notification: Ignoring invalid meta information.");
      break;
    }

    if (0 != av2notification_meta(aTHX_(AV *) SvRV(*tmp), &n->meta)) {
      plugin_notification_meta_free(n->meta);
      n->meta = NULL;
      return -1;
    }
    break;
  }
  return 0;
}