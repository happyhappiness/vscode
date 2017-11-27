static int rra_get(char ***ret, const value_list_t *vl, /* {{{ */
                   const rrdcreate_config_t *cfg) {
  char **rra_def;
  int rra_num;

  int *rts;
  int rts_num;

  int rra_max;

  int cdp_num;
  int cdp_len;

  /* The stepsize we use here: If it is user-set, use it. If not, use the
   * interval of the value-list. */
  int ss;

  if (cfg->rrarows <= 0) {
    *ret = NULL;
    return (-1);
  }

  if ((cfg->xff < 0) || (cfg->xff >= 1.0)) {
    *ret = NULL;
    return (-1);
  }

  if (cfg->stepsize > 0)
    ss = cfg->stepsize;
  else
    ss = (int)CDTIME_T_TO_TIME_T(vl->interval);
  if (ss <= 0) {
    *ret = NULL;
    return (-1);
  }

  /* Use the configured timespans or fall back to the built-in defaults */
  if (cfg->timespans_num != 0) {
    rts = cfg->timespans;
    rts_num = cfg->timespans_num;
  } else {
    rts = rra_timespans;
    rts_num = rra_timespans_num;
  }

  rra_max = rts_num * rra_types_num;
  assert(rra_max > 0);

  if ((rra_def = calloc(rra_max + 1, sizeof(*rra_def))) == NULL)
    return (-1);
  rra_num = 0;

  cdp_len = 0;
  for (int i = 0; i < rts_num; i++) {
    int span = rts[i];

    if ((span / ss) < cfg->rrarows)
      span = ss * cfg->rrarows;

    if (cdp_len == 0)
      cdp_len = 1;
    else
      cdp_len = (int)floor(((double)span) / ((double)(cfg->rrarows * ss)));

    cdp_num = (int)ceil(((double)span) / ((double)(cdp_len * ss)));

    for (int j = 0; j < rra_types_num; j++) {
      char buffer[128];
      int status;

      if (rra_num >= rra_max)
        break;

      status = ssnprintf(buffer, sizeof(buffer), "RRA:%s:%.10f:%u:%u",
                         rra_types[j], cfg->xff, cdp_len, cdp_num);

      if ((status < 0) || ((size_t)status >= sizeof(buffer))) {
        ERROR("rra_get: Buffer would have been truncated.");
        continue;
      }

      rra_def[rra_num++] = sstrdup(buffer);
    }
  }

  if (rra_num <= 0) {
    sfree(rra_def);
    return (0);
  }

  *ret = rra_def;
  return (rra_num);
}