static int value_list_to_kairosdb (char *buffer, size_t buffer_size, /* {{{ */
                const data_set_t *ds, const value_list_t *vl, int store_rates)
{
  char temp[512];
  size_t offset = 0;
  int status;

  memset (buffer, 0, buffer_size);

#define BUFFER_ADD(...) do { \
  status = ssnprintf (buffer + offset, buffer_size - offset, \
      __VA_ARGS__); \
  if (status < 1) \
    return (-1); \
  else if (((size_t) status) >= (buffer_size - offset)) \
    return (-ENOMEM); \
  else \
    offset += ((size_t) status); \
} while (0)

#define BUFFER_ADD_KEYVAL(key, value) do { \
  status = kairosdb_escape_string (temp, sizeof (temp), (value)); \
  if (status != 0) \
    return (status); \
  BUFFER_ADD (",\"%s\": %s", (key), temp); \
} while (0)

  for (size_t i = 0; i < ds->ds_num; i++)
  {
    /* All value lists have a leading comma. The first one will be replaced with
     * a square bracket in `format_kairosdb_finalize'. */
    BUFFER_ADD (",{");

    BUFFER_ADD ("\"name\":\"collectd");

    BUFFER_ADD (".%s", vl->plugin);

    status = values_to_kairosdb (temp, sizeof (temp), ds, vl, store_rates, i);
    if (status != 0)
      return (status);

    BUFFER_ADD ("\", \"datapoints\": %s", temp);

    /*
     * Now adds meta data to metric as tags
     */

    memset (temp, 0, sizeof(temp));

    BUFFER_ADD (", \"tags\":\{");

    BUFFER_ADD ("\"host\": \"%s\"", vl->host);
    if (strlen(vl->plugin_instance))
      BUFFER_ADD_KEYVAL ("plugin_instance", vl->plugin_instance);
    BUFFER_ADD_KEYVAL ("type", vl->type);
    if (strlen(vl->type_instance))
      BUFFER_ADD_KEYVAL ("type_instance", vl->type_instance);
    if (ds->ds_num != 1)
      BUFFER_ADD_KEYVAL ("ds", ds->ds[i].name);
    BUFFER_ADD ("}}");
  } /* for ds->ds_num */

#undef BUFFER_ADD_KEYVAL
#undef BUFFER_ADD

  DEBUG ("format_kairosdb: value_list_to_kairosdb: buffer = %s;", buffer);

  return (0);
}