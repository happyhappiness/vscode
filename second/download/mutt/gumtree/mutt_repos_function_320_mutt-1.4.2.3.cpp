static char *extract_message_id (const char *s)
{
  const char *p;
  char *r;
  size_t l;

  if ((s = strchr (s, '<')) == NULL || (p = strchr (s, '>')) == NULL)
    return (NULL);
  l = (size_t)(p - s) + 1;
  r = safe_malloc (l + 1);
  memcpy (r, s, l);
  r[l] = 0;
  return (r);
}