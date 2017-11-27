static int av2notification_meta(pTHX_ AV *array, notification_meta_t **meta) {
  notification_meta_t **m = meta;

  int len = av_len(array);

  for (int i = 0; i <= len; ++i) {
    SV **tmp = av_fetch(array, i, 0);
    HV *hash;

    if (NULL == tmp)
      return -1;

    if (!(SvROK(*tmp) && (SVt_PVHV == SvTYPE(SvRV(*tmp))))) {
      log_warn("av2notification_meta: Skipping invalid "
               "meta information.");
      continue;
    }

    hash = (HV *)SvRV(*tmp);

    *m = smalloc(sizeof(**m));

    if (NULL == (tmp = hv_fetch(hash, "name", 4, 0))) {
      log_warn("av2notification_meta: Skipping invalid "
               "meta information.");
      free(*m);
      continue;
    }
    sstrncpy((*m)->name, SvPV_nolen(*tmp), sizeof((*m)->name));

    if (NULL == (tmp = hv_fetch(hash, "value", 5, 0))) {
      log_warn("av2notification_meta: Skipping invalid "
               "meta information.");
      free(*m);
      continue;
    }

    if (SvNOK(*tmp)) {
      (*m)->nm_value.nm_double = SvNVX(*tmp);
      (*m)->type = NM_TYPE_DOUBLE;
    } else if (SvUOK(*tmp)) {
      (*m)->nm_value.nm_unsigned_int = SvUVX(*tmp);
      (*m)->type = NM_TYPE_UNSIGNED_INT;
    } else if (SvIOK(*tmp)) {
      (*m)->nm_value.nm_signed_int = SvIVX(*tmp);
      (*m)->type = NM_TYPE_SIGNED_INT;
    } else {
      (*m)->nm_value.nm_string = sstrdup(SvPV_nolen(*tmp));
      (*m)->type = NM_TYPE_STRING;
    }

    (*m)->next = NULL;
    m = &((*m)->next);
  }
  return 0;
}