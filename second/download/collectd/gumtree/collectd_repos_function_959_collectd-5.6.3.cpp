static size_t av2value(pTHX_ char *name, AV *array, value_t *value,
                       size_t array_len) {
  const data_set_t *ds;

  if ((NULL == name) || (NULL == array) || (NULL == value) || (array_len == 0))
    return 0;

  ds = plugin_get_ds(name);
  if (NULL == ds) {
    log_err("av2value: Unknown dataset \"%s\"", name);
    return 0;
  }

  if (array_len < ds->ds_num) {
    log_warn("av2value: array does not contain enough elements for type "
             "\"%s\": got %zu, want %zu",
             name, array_len, ds->ds_num);
    return 0;
  } else if (array_len > ds->ds_num) {
    log_warn("av2value: array contains excess elements for type \"%s\": got "
             "%zu, want %zu",
             name, array_len, ds->ds_num);
  }

  for (size_t i = 0; i < ds->ds_num; ++i) {
    SV **tmp = av_fetch(array, i, 0);

    if (NULL != tmp) {
      if (DS_TYPE_COUNTER == ds->ds[i].type)
        value[i].counter = SvIV(*tmp);
      else if (DS_TYPE_GAUGE == ds->ds[i].type)
        value[i].gauge = SvNV(*tmp);
      else if (DS_TYPE_DERIVE == ds->ds[i].type)
        value[i].derive = SvIV(*tmp);
      else if (DS_TYPE_ABSOLUTE == ds->ds[i].type)
        value[i].absolute = SvIV(*tmp);
    } else {
      return 0;
    }
  }

  return ds->ds_num;
}