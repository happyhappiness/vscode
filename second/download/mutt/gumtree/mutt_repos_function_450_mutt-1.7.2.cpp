static BUFFY* buffy_get (const char *path)
{
  BUFFY *cur;
  char *epath;

  if (!path)
    return NULL;

  epath = safe_strdup(path);
  mutt_expand_path(epath, mutt_strlen(epath));

  for (cur = Incoming; cur; cur = cur->next)
  {
    /* must be done late because e.g. IMAP delimiter may change */
    mutt_expand_path (cur->path, sizeof (cur->path));
    if (!mutt_strcmp(cur->path, path))
    {
      FREE (&epath);
      return cur;
    }
  }

  FREE (&epath);
  return NULL;
}