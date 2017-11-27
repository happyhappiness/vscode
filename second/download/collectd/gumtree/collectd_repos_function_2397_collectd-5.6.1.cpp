int parse_value (const char *value_orig, value_t *ret_value, int ds_type)
{
  char *value;
  char *endptr = NULL;
  size_t value_len;

  if (value_orig == NULL)
    return (EINVAL);

  value = strdup (value_orig);
  if (value == NULL)
    return (ENOMEM);
  value_len = strlen (value);

  while ((value_len > 0) && isspace ((int) value[value_len - 1]))
  {
    value[value_len - 1] = 0;
    value_len--;
  }

  switch (ds_type)
  {
    case DS_TYPE_COUNTER:
      ret_value->counter = (counter_t) strtoull (value, &endptr, 0);
      break;

    case DS_TYPE_GAUGE:
      ret_value->gauge = (gauge_t) strtod (value, &endptr);
      break;

    case DS_TYPE_DERIVE:
      ret_value->derive = (derive_t) strtoll (value, &endptr, 0);
      break;

    case DS_TYPE_ABSOLUTE:
      ret_value->absolute = (absolute_t) strtoull (value, &endptr, 0);
      break;

    default:
      sfree (value);
      ERROR ("parse_value: Invalid data source type: %i.", ds_type);
      return -1;
  }

  if (value == endptr) {
    ERROR ("parse_value: Failed to parse string as %s: \"%s\".",
        DS_TYPE_TO_STRING (ds_type), value);
    sfree (value);
    return -1;
  }
  else if ((NULL != endptr) && ('\0' != *endptr))
    INFO ("parse_value: Ignoring trailing garbage \"%s\" after %s value. "
        "Input string was \"%s\".",
        endptr, DS_TYPE_TO_STRING (ds_type), value_orig);

  sfree (value);
  return 0;
}