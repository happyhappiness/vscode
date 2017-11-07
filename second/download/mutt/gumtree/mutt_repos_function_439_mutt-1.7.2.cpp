static BUFFY *buffy_new (const char *path)
{
  BUFFY* buffy;
  char rp[PATH_MAX] = "";
  char *r = NULL;

  buffy = (BUFFY *) safe_calloc (1, sizeof (BUFFY));
  strfcpy (buffy->path, path, sizeof (buffy->path));
  r = realpath (path, rp);
  strfcpy (buffy->realpath, r ? rp : path, sizeof (buffy->realpath));
  buffy->next = NULL;
  buffy->magic = 0;

  return buffy;
}