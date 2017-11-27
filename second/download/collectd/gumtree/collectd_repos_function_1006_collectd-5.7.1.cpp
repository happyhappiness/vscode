static int hv2data_source(pTHX_ HV *hash, data_source_t *ds) {
  SV **tmp = NULL;

  if ((NULL == hash) || (NULL == ds))
    return -1;

  if (NULL != (tmp = hv_fetch(hash, "name", 4, 0))) {
    sstrncpy(ds->name, SvPV_nolen(*tmp), sizeof(ds->name));
  } else {
    log_err("hv2data_source: No DS name given.");
    return -1;
  }

  if (NULL != (tmp = hv_fetch(hash, "type", 4, 0))) {
    ds->type = SvIV(*tmp);

    if ((DS_TYPE_COUNTER != ds->type) && (DS_TYPE_GAUGE != ds->type) &&
        (DS_TYPE_DERIVE != ds->type) && (DS_TYPE_ABSOLUTE != ds->type)) {
      log_err("hv2data_source: Invalid DS type.");
      return -1;
    }
  } else {
    ds->type = DS_TYPE_COUNTER;
  }

  if (NULL != (tmp = hv_fetch(hash, "min", 3, 0)))
    ds->min = SvNV(*tmp);
  else
    ds->min = NAN;

  if (NULL != (tmp = hv_fetch(hash, "max", 3, 0)))
    ds->max = SvNV(*tmp);
  else
    ds->max = NAN;
  return 0;
}