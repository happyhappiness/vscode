static char *lcc_strdup (const char *str) /* {{{ */
{
  size_t strsize;
  char *ret;

  strsize = strlen (str) + 1;
  ret = (char *) malloc (strsize);
  if (ret != NULL)
    memcpy (ret, str, strsize);
  return (ret);
}