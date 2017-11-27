static int value_list_to_string_multiple(char *buffer, int buffer_len,
                                         const data_set_t *ds,
                                         const value_list_t *vl) {
  int offset;
  int status;
  time_t tt;

  memset(buffer, '\0', buffer_len);

  tt = CDTIME_T_TO_TIME_T(vl->time);
  status = ssnprintf(buffer, buffer_len, "%u", (unsigned int)tt);
  if ((status < 1) || (status >= buffer_len))
    return (-1);
  offset = status;

  for (size_t i = 0; i < ds->ds_num; i++) {
    if ((ds->ds[i].type != DS_TYPE_COUNTER) &&
        (ds->ds[i].type != DS_TYPE_GAUGE) &&
        (ds->ds[i].type != DS_TYPE_DERIVE) &&
        (ds->ds[i].type != DS_TYPE_ABSOLUTE))
      return (-1);

    if (ds->ds[i].type == DS_TYPE_COUNTER)
      status = ssnprintf(buffer + offset, buffer_len - offset, ":%llu",
                         vl->values[i].counter);
    else if (ds->ds[i].type == DS_TYPE_GAUGE)
      status = ssnprintf(buffer + offset, buffer_len - offset, ":" GAUGE_FORMAT,
                         vl->values[i].gauge);
    else if (ds->ds[i].type == DS_TYPE_DERIVE)
      status = ssnprintf(buffer + offset, buffer_len - offset, ":%" PRIi64,
                         vl->values[i].derive);
    else /*if (ds->ds[i].type == DS_TYPE_ABSOLUTE) */
      status = ssnprintf(buffer + offset, buffer_len - offset, ":%" PRIu64,
                         vl->values[i].absolute);

    if ((status < 1) || (status >= (buffer_len - offset)))
      return (-1);

    offset += status;
  } /* for ds->ds_num */

  return (0);
}