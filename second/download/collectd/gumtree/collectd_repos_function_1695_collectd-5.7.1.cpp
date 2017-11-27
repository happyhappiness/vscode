static int statsd_parse_value(char const *str, value_t *ret_value) /* {{{ */
{
  char *endptr = NULL;

  ret_value->gauge = (gauge_t)strtod(str, &endptr);
  if ((str == endptr) || ((endptr != NULL) && (*endptr != 0)))
    return (-1);

  return (0);
}