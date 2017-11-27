static int olsrd_cb_links(int lineno, /* {{{ */
                          size_t fields_num, char **fields) {
  /* Fields:
   *  0 = Local IP
   *  1 = Remote IP
   *  2 = Hyst.
   *  3 = LQ
   *  4 = NLQ
   *  5 = Cost */

  static uint32_t links_num;
  static double lq_sum;
  static uint32_t lq_num;
  static double nlq_sum;
  static uint32_t nlq_num;

  double lq;
  double nlq;

  char *endptr;

  if (config_want_links == OLSRD_WANT_NOT)
    return (0);

  /* Special handling of the first line. */
  if (lineno <= 0) {
    links_num = 0;
    lq_sum = 0.0;
    lq_num = 0;
    nlq_sum = 0.0;
    nlq_num = 0;

    return (0);
  }

  /* Special handling of the last line. */
  if (fields_num == 0) {
    DEBUG("olsrd plugin: Number of links: %" PRIu32, links_num);
    olsrd_submit(/* p.-inst = */ "links", /* type = */ "links",
                 /* t.-inst = */ NULL, (gauge_t)links_num);

    lq = NAN;
    if (lq_num > 0)
      lq = lq_sum / ((double)lq_num);
    DEBUG("olsrd plugin: Average  LQ: %g", lq);
    olsrd_submit(/* p.-inst = */ "links", /* type = */ "signal_quality",
                 "average-lq", lq);

    nlq = NAN;
    if (nlq_num > 0)
      nlq = nlq_sum / ((double)nlq_num);
    DEBUG("olsrd plugin: Average NLQ: %g", nlq);
    olsrd_submit(/* p.-inst = */ "links", /* type = */ "signal_quality",
                 "average-nlq", nlq);

    return (0);
  }

  if (fields_num != 6)
    return (-1);

  links_num++;

  errno = 0;
  endptr = NULL;
  lq = strtod(fields[3], &endptr);
  if ((errno != 0) || (endptr == fields[3])) {
    ERROR("olsrd plugin: Cannot parse link quality: %s", fields[3]);
  } else {
    if (!isnan(lq)) {
      lq_sum += lq;
      lq_num++;
    }

    if (config_want_links == OLSRD_WANT_DETAIL) {
      char type_instance[DATA_MAX_NAME_LEN];

      ssnprintf(type_instance, sizeof(type_instance), "%s-%s-lq", fields[0],
                fields[1]);

      DEBUG("olsrd plugin: links: type_instance = %s;  lq = %g;", type_instance,
            lq);
      olsrd_submit(/* p.-inst = */ "links", /* type = */ "signal_quality",
                   type_instance, lq);
    }
  }

  errno = 0;
  endptr = NULL;
  nlq = strtod(fields[4], &endptr);
  if ((errno != 0) || (endptr == fields[4])) {
    ERROR("olsrd plugin: Cannot parse neighbor link quality: %s", fields[4]);
  } else {
    if (!isnan(nlq)) {
      nlq_sum += nlq;
      nlq_num++;
    }

    if (config_want_links == OLSRD_WANT_DETAIL) {
      char type_instance[DATA_MAX_NAME_LEN];

      ssnprintf(type_instance, sizeof(type_instance), "%s-%s-rx", fields[0],
                fields[1]);

      DEBUG("olsrd plugin: links: type_instance = %s; nlq = %g;", type_instance,
            lq);
      olsrd_submit(/* p.-inst = */ "links", /* type = */ "signal_quality",
                   type_instance, nlq);
    }
  }

  return (0);
}