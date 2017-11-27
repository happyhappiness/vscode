static int cna_config_get_interval(const oconfig_item_t *ci, /* {{{ */
                                   cna_interval_t *out_interval) {
  cdtime_t tmp = 0;
  int status;

  status = cf_util_get_cdtime(ci, &tmp);
  if (status != 0)
    return (status);

  out_interval->interval = tmp;
  out_interval->last_read = 0;

  return (0);
}