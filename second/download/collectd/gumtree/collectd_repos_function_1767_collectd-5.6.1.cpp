static int olsrd_cb_topology (int lineno, /* {{{ */
    size_t fields_num, char **fields)
{
  /* Fields:
   *  0 = Dest. IP
   *  1 = Last hop IP
   *  2 = LQ
   *  3 = NLQ
   *  4 = Cost */

  static double   lq_sum;
  static uint32_t lq_num;

  static uint32_t links_num;

  double lq;
  char *endptr;

  if (config_want_topology == OLSRD_WANT_NOT)
    return (0);

  /* Special handling of the first line */
  if (lineno <= 0)
  {
    lq_sum = 0.0;
    lq_num = 0;
    links_num = 0;

    return (0);
  }

  /* Special handling after the last line */
  if (fields_num == 0)
  {
    DEBUG ("olsrd plugin: topology: Number of links: %"PRIu32, links_num);
    olsrd_submit (/* p.-inst = */ "topology", /* type = */ "links",
        /* t.-inst = */ NULL, (gauge_t) links_num);

    lq = NAN;
    if (lq_num > 0)
      lq = lq_sum / ((double) lq_sum);
    DEBUG ("olsrd plugin: topology: Average link quality: %g", lq);
    olsrd_submit (/* p.-inst = */ "topology", /* type = */ "signal_quality",
        /* t.-inst = */ "average", lq);

    return (0);
  }

  if (fields_num != 5)
    return (-1);

  links_num++;

  errno = 0;
  endptr = NULL;
  lq = strtod (fields[2], &endptr);
  if ((errno != 0) || (endptr == fields[2]))
  {
    ERROR ("olsrd plugin: Unable to parse LQ: %s", fields[2]);
  }
  else
  {
    if (!isnan (lq))
    {
      lq_sum += lq;
      lq_num++;
    }

    if (config_want_topology == OLSRD_WANT_DETAIL)
    {
      char type_instance[DATA_MAX_NAME_LEN] = { 0 };

      ssnprintf (type_instance, sizeof (type_instance), "%s-%s-lq",
          fields[0], fields[1]);
      DEBUG ("olsrd plugin: type_instance = %s; lq = %g;", type_instance, lq);
      olsrd_submit (/* p.-inst = */ "topology", /* type = */ "signal_quality",
          type_instance, lq);
    }
  }

  if (config_want_topology == OLSRD_WANT_DETAIL)
  {
    double nlq;

    errno = 0;
    endptr = NULL;
    nlq = strtod (fields[3], &endptr);
    if ((errno != 0) || (endptr == fields[3]))
    {
      ERROR ("olsrd plugin: Unable to parse NLQ: %s", fields[3]);
    }
    else
    {
      char type_instance[DATA_MAX_NAME_LEN] = { 0 };

      ssnprintf (type_instance, sizeof (type_instance), "%s-%s-nlq",
          fields[0], fields[1]);
      DEBUG ("olsrd plugin: type_instance = %s; nlq = %g;", type_instance, nlq);
      olsrd_submit (/* p.-inst = */ "topology", /* type = */ "signal_quality",
          type_instance, nlq);
    }
  }

  return (0);
}