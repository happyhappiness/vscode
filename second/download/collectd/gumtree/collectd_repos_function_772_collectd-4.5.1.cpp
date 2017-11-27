static int default_callback (const char *str,
    char * const *matches, size_t matches_num, void *user_data)
{
  cu_match_value_t *data = (cu_match_value_t *) user_data;

  if (data->ds_type & UTILS_MATCH_DS_TYPE_GAUGE)
  {
    gauge_t value;
    char *endptr = NULL;

    if (matches_num < 2)
      return (-1);

    value = strtod (matches[1], &endptr);
    if (matches[1] == endptr)
      return (-1);

    if ((data->values_num == 0)
	|| (data->ds_type & UTILS_MATCH_CF_GAUGE_LAST))
    {
      data->value.gauge = value;
    }
    else if (data->ds_type & UTILS_MATCH_CF_GAUGE_AVERAGE)
    {
      double f = ((double) data->values_num)
	/ ((double) (data->values_num + 1));
      data->value.gauge = (data->value.gauge * f) + (value * (1.0 - f));
    }
    else if (data->ds_type & UTILS_MATCH_CF_GAUGE_MIN)
    {
      if (data->value.gauge > value)
	data->value.gauge = value;
    }
    else if (data->ds_type & UTILS_MATCH_CF_GAUGE_MAX)
    {
      if (data->value.gauge < value)
	data->value.gauge = value;
    }
    else
    {
      ERROR ("utils_match: default_callback: obj->ds_type is invalid!");
      return (-1);
    }

    data->values_num++;
  }
  else if (data->ds_type & UTILS_MATCH_DS_TYPE_COUNTER)
  {
    counter_t value;
    char *endptr = NULL;

    if (data->ds_type & UTILS_MATCH_CF_COUNTER_INC)
    {
      data->value.counter++;
      data->values_num++;
      return (0);
    }

    if (matches_num < 2)
      return (-1);

    value = strtoll (matches[1], &endptr, 0);
    if (matches[1] == endptr)
      return (-1);

    if (data->ds_type & UTILS_MATCH_CF_COUNTER_SET)
      data->value.counter = value;
    else if (data->ds_type & UTILS_MATCH_CF_COUNTER_ADD)
      data->value.counter += value;
    else
    {
      ERROR ("utils_match: default_callback: obj->ds_type is invalid!");
      return (-1);
    }

    data->values_num++;
  }
  else
  {
    ERROR ("utils_match: default_callback: obj->ds_type is invalid!");
    return (-1);
  }

  return (0);
}