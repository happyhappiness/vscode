void mutt_adv_mktemp (char *s, size_t l)
{
  char prefix[_POSIX_PATH_MAX];
  char *suffix;
  struct stat sb;

  if (s[0] == '\0')
  {
    mutt_mktemp (s, l);
  }
  else
  {
    strfcpy (prefix, s, sizeof (prefix));
    mutt_sanitize_filename (prefix, 1);
    snprintf (s, l, "%s/%s", NONULL (Tempdir), prefix);
    if (lstat (s, &sb) == -1 && errno == ENOENT)
      return;

    if ((suffix = strrchr (prefix, '.')) != NULL)
    {
      *suffix = 0;
      ++suffix;
    }
    mutt_mktemp_pfx_sfx (s, l, prefix, suffix);
  }
}