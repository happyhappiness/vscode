static int agg_instance_update(agg_instance_t *inst, /* {{{ */
                               data_set_t const *ds, value_list_t const *vl) {
  gauge_t *rate;

  if (ds->ds_num != 1) {
    ERROR("aggregation plugin: The \"%s\" type (data set) has more than one "
          "data source. This is currently not supported by this plugin. "
          "Sorry.",
          ds->type);
    return (EINVAL);
  }

  rate = uc_get_rate(ds, vl);
  if (rate == NULL) {
    char ident[6 * DATA_MAX_NAME_LEN];
    FORMAT_VL(ident, sizeof(ident), vl);
    ERROR("aggregation plugin: Unable to read the current rate of \"%s\".",
          ident);
    return (ENOENT);
  }

  if (isnan(rate[0])) {
    sfree(rate);
    return (0);
  }

  pthread_mutex_lock(&inst->lock);

  inst->num++;
  inst->sum += rate[0];
  inst->squares_sum += (rate[0] * rate[0]);

  if (isnan(inst->min) || (inst->min > rate[0]))
    inst->min = rate[0];
  if (isnan(inst->max) || (inst->max < rate[0]))
    inst->max = rate[0];

  pthread_mutex_unlock(&inst->lock);

  sfree(rate);
  return (0);
}