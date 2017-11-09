static const char *
find_hook (int type, const char *path)
{
  if (!path)
    return NULL;

  const char *c = mutt_find_hook (type, path);
  if (!c || !*c)
    return NULL;

  return c;
}