void mutt_adv_mktemp (char *s, size_t l)
{
  char buf[_POSIX_PATH_MAX];
  char tmp[_POSIX_PATH_MAX];
  char *period;
  size_t sl;
  struct stat sb;
  
  strfcpy (buf, NONULL (Tempdir), sizeof (buf));
  mutt_expand_path (buf, sizeof (buf));
  if (s[0] == '\0')
  {
    snprintf (s, l, "%s/muttXXXXXX", buf);
    mktemp (s);
  }
  else
  {
    strfcpy (tmp, s, sizeof (tmp));
    mutt_sanitize_filename (tmp, 1);
    snprintf (s, l, "%s/%s", buf, tmp);
    if (lstat (s, &sb) == -1 && errno == ENOENT)
      return;
    if ((period = strrchr (tmp, '.')) != NULL)
      *period = 0;
    snprintf (s, l, "%s/%s.XXXXXX", buf, tmp);
    mktemp (s);
    if (period != NULL)
    {
      *period = '.';
      sl = mutt_strlen(s);
      strfcpy(s + sl, period, l - sl);
    }
  }
}