int parse_value (const char *value, value_t *ret_value, int ds_type)
{
  char *endptr = NULL;

  switch (ds_type)
  {
    case DS_TYPE_COUNTER:
      ret_value->counter = (counter_t) strtoull (value, &endptr, 0);
      break;

    case DS_TYPE_GAUGE:
      ret_value->gauge = (gauge_t) strtod (value, &endptr);
      break;

    case DS_TYPE_DERIVE:
      ret_value->counter = (derive_t) strtoll (value, &endptr, 0);
      break;

    case DS_TYPE_ABSOLUTE:
      ret_value->counter = (absolute_t) strtoull (value, &endptr, 0);
      break;

    default:
      ERROR ("parse_value: Invalid data source type: %i.", ds_type);
      return -1;
  }

  if (value == endptr) {
    ERROR ("parse_value: Failed to parse string as number: %s.", value);
    return -1;
  }
  else if ((NULL != endptr) && ('\0' != *endptr))
    WARNING ("parse_value: Ignoring trailing garbage after number: %s.",
        endptr);
  return 0;
}