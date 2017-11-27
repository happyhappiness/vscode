static int rc_config_get_xff(oconfig_item_t const *ci, double *ret) {
  double value;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_NUMBER)) {
    ERROR("rrdcached plugin: The \"%s\" needs exactly one numeric argument "
          "in the range [0.0, 1.0)",
          ci->key);
    return EINVAL;
  }

  value = ci->values[0].value.number;
  if ((value >= 0.0) && (value < 1.0)) {
    *ret = value;
    return 0;
  }

  ERROR("rrdcached plugin: The \"%s\" needs exactly one numeric argument "
        "in the range [0.0, 1.0)",
        ci->key);
  return EINVAL;
}