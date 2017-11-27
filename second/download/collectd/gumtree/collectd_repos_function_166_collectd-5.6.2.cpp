static int rc_config_get_int_positive(oconfig_item_t const *ci, int *ret) {
  int status;
  int tmp = 0;

  status = cf_util_get_int(ci, &tmp);
  if (status != 0)
    return (status);
  if (tmp < 0)
    return (EINVAL);

  *ret = tmp;
  return (0);
}