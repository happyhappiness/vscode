static int statsd_config_timer_percentile(oconfig_item_t *ci) /* {{{ */
{
  double percent = NAN;
  double *tmp;
  int status;

  status = cf_util_get_double(ci, &percent);
  if (status != 0)
    return status;

  if ((percent <= 0.0) || (percent >= 100)) {
    ERROR("statsd plugin: The value for \"%s\" must be between 0 and 100, "
          "exclusively.",
          ci->key);
    return ERANGE;
  }

  tmp =
      realloc(conf_timer_percentile,
              sizeof(*conf_timer_percentile) * (conf_timer_percentile_num + 1));
  if (tmp == NULL) {
    ERROR("statsd plugin: realloc failed.");
    return ENOMEM;
  }
  conf_timer_percentile = tmp;
  conf_timer_percentile[conf_timer_percentile_num] = percent;
  conf_timer_percentile_num++;

  return 0;
}