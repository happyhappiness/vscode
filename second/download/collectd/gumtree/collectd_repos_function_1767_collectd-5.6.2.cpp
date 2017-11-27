static int olsrd_cb_routes(int lineno, /* {{{ */
                           size_t fields_num, char **fields) {
  /* Fields:
   *  0 = Destination
   *  1 = Gateway IP
   *  2 = Metric
   *  3 = ETX
   *  4 = Interface */

  static uint32_t routes_num;
  static uint32_t metric_sum;
  static uint32_t metric_num;
  static double etx_sum;
  static uint32_t etx_num;

  uint32_t metric;
  double etx;
  char *endptr;

  if (config_want_routes == OLSRD_WANT_NOT)
    return (0);

  /* Special handling of the first line */
  if (lineno <= 0) {
    routes_num = 0;
    metric_num = 0;
    metric_sum = 0;
    etx_sum = 0.0;
    etx_num = 0;

    return (0);
  }

  /* Special handling after the last line */
  if (fields_num == 0) {
    double metric_avg;

    DEBUG("olsrd plugin: Number of routes: %" PRIu32, routes_num);
    olsrd_submit(/* p.-inst = */ "routes", /* type = */ "routes",
                 /* t.-inst = */ NULL, (gauge_t)routes_num);

    metric_avg = NAN;
    if (metric_num > 0)
      metric_avg = ((double)metric_sum) / ((double)metric_num);
    DEBUG("olsrd plugin: Average metric: %g", metric_avg);
    olsrd_submit(/* p.-inst = */ "routes", /* type = */ "route_metric",
                 "average", metric_avg);

    etx = NAN;
    if (etx_num > 0)
      etx = etx_sum / ((double)etx_sum);
    DEBUG("olsrd plugin: Average ETX: %g", etx);
    olsrd_submit(/* p.-inst = */ "routes", /* type = */ "route_etx", "average",
                 etx);

    return (0);
  }

  if (fields_num != 5)
    return (-1);

  routes_num++;

  errno = 0;
  endptr = NULL;
  metric = (uint32_t)strtoul(fields[2], &endptr, 0);
  if ((errno != 0) || (endptr == fields[2])) {
    ERROR("olsrd plugin: Unable to parse metric: %s", fields[2]);
  } else {
    metric_num++;
    metric_sum += metric;

    if (config_want_routes == OLSRD_WANT_DETAIL) {
      DEBUG("olsrd plugin: destination = %s; metric = %" PRIu32 ";", fields[0],
            metric);
      olsrd_submit(/* p.-inst = */ "routes", /* type = */ "route_metric",
                   /* t.-inst = */ fields[0], (gauge_t)metric);
    }
  }

  errno = 0;
  endptr = NULL;
  etx = strtod(fields[3], &endptr);
  if ((errno != 0) || (endptr == fields[3])) {
    ERROR("olsrd plugin: Unable to parse ETX: %s", fields[3]);
  } else {
    if (!isnan(etx)) {
      etx_sum += etx;
      etx_num++;
    }

    if (config_want_routes == OLSRD_WANT_DETAIL) {
      DEBUG("olsrd plugin: destination = %s; etx = %g;", fields[0], etx);
      olsrd_submit(/* p.-inst = */ "routes", /* type = */ "route_etx",
                   /* t.-inst = */ fields[0], etx);
    }
  }

  return (0);
}