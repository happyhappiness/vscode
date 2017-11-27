static int latency_config_add_percentile(latency_config_t *conf,
                                         oconfig_item_t *ci,
                                         const char *plugin) {
  double percent;
  int status = cf_util_get_double(ci, &percent);
  if (status != 0)
    return status;

  if ((percent <= 0.0) || (percent >= 100)) {
    ERROR("%s plugin: The value for \"%s\" must be between 0 and 100, "
          "exclusively.",
          plugin, ci->key);
    return ERANGE;
  }

  double *tmp = realloc(conf->percentile,
                        sizeof(*conf->percentile) * (conf->percentile_num + 1));
  if (tmp == NULL) {
    ERROR("%s plugin: realloc failed.", plugin);
    return ENOMEM;
  }
  conf->percentile = tmp;
  conf->percentile[conf->percentile_num] = percent;
  conf->percentile_num++;

  return 0;
}