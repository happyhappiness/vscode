static int notification_meta2av(pTHX_ notification_meta_t *meta, AV *array) {
  int meta_num = 0;

  while (meta) {
    ++meta_num;
    meta = meta->next;
  }

  av_extend(array, meta_num);

  for (int i = 0; NULL != meta; meta = meta->next, ++i) {
    HV *m = newHV();
    SV *value;

    if (NULL == hv_store(m, "name", 4, newSVpv(meta->name, 0), 0))
      return -1;

    if (NM_TYPE_STRING == meta->type)
      value = newSVpv(meta->nm_value.nm_string, 0);
    else if (NM_TYPE_SIGNED_INT == meta->type)
      value = newSViv(meta->nm_value.nm_signed_int);
    else if (NM_TYPE_UNSIGNED_INT == meta->type)
      value = newSVuv(meta->nm_value.nm_unsigned_int);
    else if (NM_TYPE_DOUBLE == meta->type)
      value = newSVnv(meta->nm_value.nm_double);
    else if (NM_TYPE_BOOLEAN == meta->type)
      value = meta->nm_value.nm_boolean ? &PL_sv_yes : &PL_sv_no;
    else
      return -1;

    if (NULL == hv_store(m, "value", 5, value, 0)) {
      sv_free(value);
      return -1;
    }

    if (NULL == av_store(array, i, newRV_noinc((SV *)m))) {
      hv_clear(m);
      hv_undef(m);
      return -1;
    }
  }
  return 0;
}