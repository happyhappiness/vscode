void mutt_str_replace (char **p, const char *s)
{
  safe_free ((void **) p);
  *p = safe_strdup (s);
}