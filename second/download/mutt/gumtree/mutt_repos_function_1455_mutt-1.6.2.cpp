static int mh_read_sequences (struct mh_sequences *mhs, const char *path)
{
  FILE *fp;
  int line = 1;
  char *buff = NULL;
  char *t;
  size_t sz = 0;

  short f;
  int first, last, rc = 0;

  char pathname[_POSIX_PATH_MAX];
  snprintf (pathname, sizeof (pathname), "%s/.mh_sequences", path);

  if (!(fp = fopen (pathname, "r")))
    return 0; /* yes, ask callers to silently ignore the error */

  while ((buff = mutt_read_line (buff, &sz, fp, &line, 0)))
  {
    if (!(t = strtok (buff, " \t:")))
      continue;

    if (!mutt_strcmp (t, MhUnseen))
      f = MH_SEQ_UNSEEN;
    else if (!mutt_strcmp (t, MhFlagged))
      f = MH_SEQ_FLAGGED;
    else if (!mutt_strcmp (t, MhReplied))
      f = MH_SEQ_REPLIED;
    else			/* unknown sequence */
      continue;

    while ((t = strtok (NULL, " \t:")))
    {
      if (mh_read_token (t, &first, &last) < 0)
      {
	mhs_free_sequences (mhs);
	rc = -1;
	goto out;
      }
      for (; first <= last; first++)
	mhs_set (mhs, first, f);
    }
  }

  rc = 0;

out:
  FREE (&buff);
  safe_fclose (&fp);
  return rc;
}