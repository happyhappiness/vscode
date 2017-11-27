static int value_list_to_json (char *buffer, size_t buffer_size, /* {{{ */
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

  /* All value lists have a leading comma. The first one will be replaced with
   * a square bracket in `format_json_finalize'. */
  BUFFER_ADD (",{");

  status = values_to_json (temp, sizeof (temp), ds, vl, store_rates);
  if (status != 0)
    return (status);
  BUFFER_ADD ("\"values\":%s", temp);

  status = dstypes_to_json (temp, sizeof (temp), ds, vl);
  if (status != 0)
    return (status);
  BUFFER_ADD (",\"dstypes\":%s", temp);

  status = dsnames_to_json (temp, sizeof (temp), ds, vl);
  if (status != 0)
    return (status);
  BUFFER_ADD (",\"dsnames\":%s", temp);

  BUFFER_ADD (",\"time\":%lu", (unsigned long) vl->time);
  BUFFER_ADD (",\"interval\":%i", vl->interval);

#define BUFFER_ADD_KEYVAL(key, value) do { \
  status = escape_string (temp, sizeof (temp), (value)); \
  if (status != 0) \
    return (status); \
  BUFFER_ADD (",\"%s\":%s", (key), temp); \
} while (0)

  BUFFER_ADD_KEYVAL ("host", vl->host);
  BUFFER_ADD_KEYVAL ("plugin", vl->plugin);
  BUFFER_ADD_KEYVAL ("plugin_instance", vl->plugin_instance);
  BUFFER_ADD_KEYVAL ("type", vl->type);
  BUFFER_ADD_KEYVAL ("type_instance", vl->type_instance);

  BUFFER_ADD ("}");

#undef BUFFER_ADD_KEYVAL
#undef BUFFER_ADD

  DEBUG ("format_json: value_list_to_json: buffer = %s;", buffer);

  return (0);
}