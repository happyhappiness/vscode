static int latency_config_add_bucket(latency_config_t *conf, oconfig_item_t *ci,
                                     const char *plugin) {
  if ((ci->values_num != 2) || (ci->values[0].type != OCONFIG_TYPE_NUMBER) ||
      (ci->values[1].type != OCONFIG_TYPE_NUMBER)) {
    ERROR("%s plugin: \"%s\" requires exactly two numeric arguments.", plugin,
          ci->key);
    return EINVAL;
  }

  if (ci->values[1].value.number &&
      ci->values[1].value.number <= ci->values[0].value.number) {
    ERROR("%s plugin: MIN must be less than MAX in \"%s\".", plugin, ci->key);
    return ERANGE;
  }

  if (ci->values[0].value.number < 0) {
    ERROR("%s plugin: MIN must be greater then or equal to zero in \"%s\".",
          plugin, ci->key);
    return ERANGE;
  }

  latency_bucket_t *tmp =
      realloc(conf->buckets, sizeof(*conf->buckets) * (conf->buckets_num + 1));
  if (tmp == NULL) {
    ERROR("%s plugin: realloc failed.", plugin);
    return ENOMEM;
  }
  conf->buckets = tmp;
  conf->buckets[conf->buckets_num].lower_bound =
      DOUBLE_TO_CDTIME_T(ci->values[0].value.number);
  conf->buckets[conf->buckets_num].upper_bound =
      DOUBLE_TO_CDTIME_T(ci->values[1].value.number);
  conf->buckets_num++;

  return 0;
}