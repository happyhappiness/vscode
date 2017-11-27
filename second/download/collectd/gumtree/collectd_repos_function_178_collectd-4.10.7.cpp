static int value_list_to_string (char *buffer, int buffer_len,
    const data_set_t *ds, const value_list_t *vl)
{
  int offset;
  int status;
  int i;

  assert (0 == strcmp (ds->type, vl->type));

  memset (buffer, '\0', buffer_len);

  status = ssnprintf (buffer, buffer_len, "%u", (unsigned int) vl->time);
  if ((status < 1) || (status >= buffer_len))
    return (-1);
  offset = status;

  for (i = 0; i < ds->ds_num; i++)
  {
    if ((ds->ds[i].type != DS_TYPE_COUNTER)
        && (ds->ds[i].type != DS_TYPE_GAUGE)
	&& (ds->ds[i].type != DS_TYPE_DERIVE)
	&& (ds->ds[i].type != DS_TYPE_ABSOLUTE))
      return (-1);

    if (ds->ds[i].type == DS_TYPE_COUNTER)
    {
      status = ssnprintf (buffer + offset, buffer_len - offset,
          ":%llu", vl->values[i].counter);
    }
    else if (ds->ds[i].type == DS_TYPE_GAUGE) 
    {
      status = ssnprintf (buffer + offset, buffer_len - offset,
          ":%f", vl->values[i].gauge);
    }
    else if (ds->ds[i].type == DS_TYPE_DERIVE) {
      status = ssnprintf (buffer + offset, buffer_len - offset,
	  ":%"PRIi64, vl->values[i].derive);
    }
    else /* if (ds->ds[i].type == DS_TYPE_ABSOLUTE) */ {
      status = ssnprintf (buffer + offset, buffer_len - offset,
	  ":%"PRIu64, vl->values[i].absolute);
 
    }

    if ((status < 1) || (status >= (buffer_len - offset)))
      return (-1);

    offset += status;
  } /* for ds->ds_num */

  return (0);
}