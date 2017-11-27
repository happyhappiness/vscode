static int hv2value_list(pTHX_ HV *hash, value_list_t *vl) {
  SV **tmp;

  if ((NULL == hash) || (NULL == vl))
    return -1;

  if (NULL == (tmp = hv_fetch(hash, "type", 4, 0))) {
    log_err("hv2value_list: No type given.");
    return -1;
  }

  sstrncpy(vl->type, SvPV_nolen(*tmp), sizeof(vl->type));

  if ((NULL == (tmp = hv_fetch(hash, "values", 6, 0))) ||
      (!(SvROK(*tmp) && (SVt_PVAV == SvTYPE(SvRV(*tmp)))))) {
    log_err("hv2value_list: No valid values given.");
    return -1;
  }

  {
    AV *array = (AV *)SvRV(*tmp);
    /* av_len returns the highest index, not the actual length. */
    size_t array_len = (size_t)(av_len(array) + 1);
    if (array_len == 0)
      return -1;

    vl->values = calloc(array_len, sizeof(*vl->values));
    vl->values_len =
        av2value(aTHX_ vl->type, (AV *)SvRV(*tmp), vl->values, array_len);
    if (vl->values_len == 0) {
      sfree(vl->values);
      return -1;
    }
  }

  if (NULL != (tmp = hv_fetch(hash, "time", 4, 0))) {
    double t = SvNV(*tmp);
    vl->time = DOUBLE_TO_CDTIME_T(t);
  }

  if (NULL != (tmp = hv_fetch(hash, "interval", 8, 0))) {
    double t = SvNV(*tmp);
    vl->interval = DOUBLE_TO_CDTIME_T(t);
  }

  if (NULL != (tmp = hv_fetch(hash, "host", 4, 0)))
    sstrncpy(vl->host, SvPV_nolen(*tmp), sizeof(vl->host));
  else
    sstrncpy(vl->host, hostname_g, sizeof(vl->host));

  if (NULL != (tmp = hv_fetch(hash, "plugin", 6, 0)))
    sstrncpy(vl->plugin, SvPV_nolen(*tmp), sizeof(vl->plugin));

  if (NULL != (tmp = hv_fetch(hash, "plugin_instance", 15, 0)))
    sstrncpy(vl->plugin_instance, SvPV_nolen(*tmp),
             sizeof(vl->plugin_instance));

  if (NULL != (tmp = hv_fetch(hash, "type_instance", 13, 0)))
    sstrncpy(vl->type_instance, SvPV_nolen(*tmp), sizeof(vl->type_instance));
  return 0;
}