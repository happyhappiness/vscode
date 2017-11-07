static BUFFY *buffy_new (const char *path)
{
  BUFFY* buffy;

  buffy = (BUFFY *) safe_calloc (1, sizeof (BUFFY));
  strfcpy (buffy->path, path, sizeof (buffy->path));
  buffy->next = NULL;
  buffy->magic = 0;

  return buffy;
}