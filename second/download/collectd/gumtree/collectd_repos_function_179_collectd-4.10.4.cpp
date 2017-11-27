static int value_list_to_filename (char *buffer, int buffer_len,
    const data_set_t *ds, const value_list_t *vl)
{
  int offset = 0;
  int status;

  assert (0 == strcmp (ds->type, vl->type));

  if (datadir != NULL)
  {
    status = ssnprintf (buffer + offset, buffer_len - offset,
        "%s/", datadir);
    if ((status < 1) || (status >= buffer_len - offset))
      return (-1);
    offset += status;
  }

  status = ssnprintf (buffer + offset, buffer_len - offset,
      "%s/", vl->host);
  if ((status < 1) || (status >= buffer_len - offset))
    return (-1);
  offset += status;

  if (strlen (vl->plugin_instance) > 0)
    status = ssnprintf (buffer + offset, buffer_len - offset,
        "%s-%s/", vl->plugin, vl->plugin_instance);
  else
    status = ssnprintf (buffer + offset, buffer_len - offset,
        "%s/", vl->plugin);
  if ((status < 1) || (status >= buffer_len - offset))
    return (-1);
  offset += status;

  if (strlen (vl->type_instance) > 0)
    status = ssnprintf (buffer + offset, buffer_len - offset,
        "%s-%s", vl->type, vl->type_instance);
  else
    status = ssnprintf (buffer + offset, buffer_len - offset,
        "%s", vl->type);
  if ((status < 1) || (status >= buffer_len - offset))
    return (-1);
  offset += status;

  strncpy (buffer + offset, ".rrd", buffer_len - offset);
  buffer[buffer_len - 1] = 0;

  return (0);
}