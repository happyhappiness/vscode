static int av2notification_meta(pTHX_ AV *array, notification_meta_t **ret_meta) {
  notification_meta_t *tail = NULL;

  int len = av_len(array);

  for (int i = 0; i <= len; ++i) {
    SV **tmp = av_fetch(array, i, 0);

    if (tmp == NULL)
      return -1;

    if (!(SvROK(*tmp) && (SVt_PVHV == SvTYPE(SvRV(*tmp))))) {
      log_warn("av2notification_meta: Skipping invalid "
               "meta information.");
      continue;
    }

    HV *hash = (HV *)SvRV(*tmp);

    notification_meta_t *m = calloc(1, sizeof(*m));
    if (m == NULL)
      return ENOMEM;

    SV **name = hv_fetch(hash, "name", strlen("name"), 0);
    if (name == NULL) {
      log_warn("av2notification_meta: Skipping invalid "
               "meta information.");
      sfree(m);
      continue;
    }
    sstrncpy(m->name, SvPV_nolen(*name), sizeof(m->name));

    SV **value = hv_fetch(hash, "value", strlen("value"), 0);
    if (value == NULL) {
      log_warn("av2notification_meta: Skipping invalid "
               "meta information.");
      sfree(m);
      continue;
    }

    if (SvNOK(*value)) {
      m->nm_value.nm_double = SvNVX(*value);
      m->type = NM_TYPE_DOUBLE;
    } else if (SvUOK(*value)) {
      m->nm_value.nm_unsigned_int = SvUVX(*value);
      m->type = NM_TYPE_UNSIGNED_INT;
    } else if (SvIOK(*value)) {
      m->nm_value.nm_signed_int = SvIVX(*value);
      m->type = NM_TYPE_SIGNED_INT;
    } else {
      m->nm_value.nm_string = sstrdup(SvPV_nolen(*value));
      m->type = NM_TYPE_STRING;
    }

    m->next = NULL;
    if (tail == NULL)
      *ret_meta = m;
    else
      tail->next = m;
    tail = m;
  }

  return 0;
}