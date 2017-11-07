static int check_charset (struct option_t *opt, const char *val)
{
  char *p, *q = NULL, *s = safe_strdup (val);
  int rc = 0, strict = strcmp (opt->option, "send_charset") == 0;

  if (!s)
    return rc;

  for (p = strtok_r (s, ":", &q); p; p = strtok_r (NULL, ":", &q))
  {
    if (!*p)
      continue;
    if (mutt_check_charset (p, strict) < 0)
    {
      rc = -1;
      break;
    }
  }

  FREE(&s);
  return rc;
}