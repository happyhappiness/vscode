static int notification2hv(pTHX_ notification_t *n, HV *hash) {
  if (NULL == hv_store(hash, "severity", 8, newSViv(n->severity), 0))
    return -1;

  if (0 != n->time) {
    double t = CDTIME_T_TO_DOUBLE(n->time);
    if (NULL == hv_store(hash, "time", 4, newSVnv(t), 0))
      return -1;
  }

  if ('\0' != *n->message)
    if (NULL == hv_store(hash, "message", 7, newSVpv(n->message, 0), 0))
      return -1;

  if ('\0' != *n->host)
    if (NULL == hv_store(hash, "host", 4, newSVpv(n->host, 0), 0))
      return -1;

  if ('\0' != *n->plugin)
    if (NULL == hv_store(hash, "plugin", 6, newSVpv(n->plugin, 0), 0))
      return -1;

  if ('\0' != *n->plugin_instance)
    if (NULL == hv_store(hash, "plugin_instance", 15,
                         newSVpv(n->plugin_instance, 0), 0))
      return -1;

  if ('\0' != *n->type)
    if (NULL == hv_store(hash, "type", 4, newSVpv(n->type, 0), 0))
      return -1;

  if ('\0' != *n->type_instance)
    if (NULL ==
        hv_store(hash, "type_instance", 13, newSVpv(n->type_instance, 0), 0))
      return -1;

  if (NULL != n->meta) {
    AV *meta = newAV();
    if ((0 != notification_meta2av(aTHX_ n->meta, meta)) ||
        (NULL == hv_store(hash, "meta", 4, newRV_noinc((SV *)meta), 0))) {
      av_clear(meta);
      av_undef(meta);
      return -1;
    }
  }
  return 0;
}