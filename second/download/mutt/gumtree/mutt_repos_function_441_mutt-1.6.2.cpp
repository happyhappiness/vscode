void mutt_buffy_setnotified (const char *path)
{
  BUFFY *buffy;

  buffy = buffy_get(path);
  if (!buffy)
    return;

  buffy->notified = 1;
  time(&buffy->last_visited);
}