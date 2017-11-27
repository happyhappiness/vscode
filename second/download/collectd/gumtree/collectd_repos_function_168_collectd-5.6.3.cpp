static int rc_config_add_timespan(int timespan) {
  int *tmp;

  if (timespan <= 0)
    return (EINVAL);

  tmp = realloc(rrdcreate_config.timespans,
                sizeof(*rrdcreate_config.timespans) *
                    (rrdcreate_config.timespans_num + 1));
  if (tmp == NULL)
    return (ENOMEM);
  rrdcreate_config.timespans = tmp;

  rrdcreate_config.timespans[rrdcreate_config.timespans_num] = timespan;
  rrdcreate_config.timespans_num++;

  return (0);
}