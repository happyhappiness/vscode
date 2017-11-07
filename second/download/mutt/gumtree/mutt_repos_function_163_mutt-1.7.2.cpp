void mutt_str_replace (char **p, const char *s)
{
  FREE (p);		/* __FREE_CHECKED__ */
  *p = safe_strdup (s);
}