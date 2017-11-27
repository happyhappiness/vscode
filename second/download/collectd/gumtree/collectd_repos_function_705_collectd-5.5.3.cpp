static int cow_read_ds2409 (const char *path)
{
  char subpath[4096];
  int status;

  status = ssnprintf (subpath, sizeof (subpath), "%s/main", path);
  if ((status > 0) && (status < sizeof (subpath)))
    cow_read_bus (subpath);

  status = ssnprintf (subpath, sizeof (subpath), "%s/aux", path);
  if ((status > 0) && (status < sizeof (subpath)))
    cow_read_bus (subpath);

  return (0);
}