static int cow_read_bus (const char *path)
{
  char *buffer;
  size_t buffer_size;
  int status;

  char *buffer_ptr;
  char *dummy;
  char *saveptr;
  char subpath[4096];

  status = OW_get (path, &buffer, &buffer_size);
  if (status < 0)
  {
    ERROR ("onewire plugin: OW_get (%s) failed. status = %#x;",
        path, status);
    return (-1);
  }
  DEBUG ("onewire plugin: OW_get (%s) returned: %s",
      path, buffer);

  dummy = buffer;
  saveptr = NULL;
  while ((buffer_ptr = strtok_r (dummy, ",/", &saveptr)) != NULL)
  {
    int i;

    dummy = NULL;

    if (strcmp ("/", path) == 0)
      status = ssnprintf (subpath, sizeof (subpath), "/%s", buffer_ptr);
    else
      status = ssnprintf (subpath, sizeof (subpath), "%s/%s",
          path, buffer_ptr);
    if ((status <= 0) || (status >= sizeof (subpath)))
      continue;

    for (i = 0; i < ow_family_features_num; i++)
    {
      if (strncmp (ow_family_features[i].family, buffer_ptr,
            strlen (ow_family_features[i].family)) != 0)
        continue;

      cow_read_values (subpath,
          buffer_ptr + strlen (ow_family_features[i].family),
          ow_family_features + i);
      break;
    }
    if (i < ow_family_features_num)
      continue;

    /* DS2409 */
    if (strncmp ("1F.", buffer_ptr, strlen ("1F.")) == 0)
    {
      cow_read_ds2409 (subpath);
      continue;
    }
  } /* while (strtok_r) */

  free (buffer);
  return (0);
}