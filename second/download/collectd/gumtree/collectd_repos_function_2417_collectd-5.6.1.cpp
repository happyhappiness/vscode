static char *fc_strdup (const char *orig) /* {{{ */
{
  size_t sz;
  char *dest;

  if (orig == NULL)
    return (NULL);

  sz = strlen (orig) + 1;
  dest = malloc (sz);
  if (dest == NULL)
    return (NULL);

  memcpy (dest, orig, sz);

  return (dest);
}