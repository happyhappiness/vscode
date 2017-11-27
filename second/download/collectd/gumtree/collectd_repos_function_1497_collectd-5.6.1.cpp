static int meta_data_keys_to_json (char *buffer, size_t buffer_size, /* {{{ */
    meta_data_t *meta, char **keys, size_t keys_num)
{
  size_t offset = 0;
  int status;

  buffer[0] = 0;

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

  for (size_t i = 0; i < keys_num; ++i)
  {
    int type;
    char *key = keys[i];

    type = meta_data_type (meta, key);
    if (type == MD_TYPE_STRING)
    {
      char *value = NULL;
      if (meta_data_get_string (meta, key, &value) == 0)
      {
        char temp[512] = "";

        status = json_escape_string (temp, sizeof (temp), value);
        sfree (value);
        if (status != 0)
          return status;

        BUFFER_ADD (",\"%s\":%s", key, temp);
      }
    }
    else if (type == MD_TYPE_SIGNED_INT)
    {
      int64_t value = 0;
      if (meta_data_get_signed_int (meta, key, &value) == 0)
        BUFFER_ADD (",\"%s\":%"PRIi64, key, value);
    }
    else if (type == MD_TYPE_UNSIGNED_INT)
    {
      uint64_t value = 0;
      if (meta_data_get_unsigned_int (meta, key, &value) == 0)
        BUFFER_ADD (",\"%s\":%"PRIu64, key, value);
    }
    else if (type == MD_TYPE_DOUBLE)
    {
      double value = 0.0;
      if (meta_data_get_double (meta, key, &value) == 0)
        BUFFER_ADD (",\"%s\":%f", key, value);
    }
    else if (type == MD_TYPE_BOOLEAN)
    {
      _Bool value = 0;
      if (meta_data_get_boolean (meta, key, &value) == 0)
        BUFFER_ADD (",\"%s\":%s", key, value ? "true" : "false");
    }
  } /* for (keys) */

  if (offset == 0)
    return (ENOENT);

  buffer[0] = '{'; /* replace leading ',' */
  BUFFER_ADD ("}");

#undef BUFFER_ADD

  return (0);
}