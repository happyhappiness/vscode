FILE *mutt_open_read (const char *path, pid_t *thepid)
{
  FILE *f;
  struct stat s;

  int len = mutt_strlen (path);

  if (path[len - 1] == '|')
  {
    /* read from a pipe */

    char *s = safe_strdup (path);

    s[len - 1] = 0;
    mutt_endwin (NULL);
    *thepid = mutt_create_filter (s, NULL, &f, NULL);
    FREE (&s);
  }
  else
  {
    if (stat (path, &s) < 0)
      return (NULL);
    if (S_ISDIR (s.st_mode))
    {
      errno = EINVAL;
      return (NULL);
    }
    f = fopen (path, "r");
    *thepid = -1;
  }
  return (f);
}