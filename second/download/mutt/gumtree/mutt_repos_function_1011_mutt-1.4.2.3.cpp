static void mh_read_sequences (struct mh_sequences *mhs, const char *path)
{
  FILE *fp;
  int line = 1;
  char *buff = NULL;
  char *t;
  size_t sz = 0;
  
  short f;
  int first, last;

  char pathname[_POSIX_PATH_MAX];
  snprintf (pathname, sizeof (pathname),  "%s/.mh_sequences", path);

  if (!(fp = fopen (pathname, "r")))
    return;

  while ((buff = mutt_read_line (buff, &sz, fp, &line)))
  {
    if (!(t = strtok (buff, " \t:")))
      continue;
    
    if (!mutt_strcmp (t, MhUnseen))
      f = MH_SEQ_UNSEEN;
    else if (!mutt_strcmp (t, MhFlagged))
      f = MH_SEQ_FLAGGED;
    else if (!mutt_strcmp (t, MhReplied))
      f = MH_SEQ_REPLIED;
    else	/* unknown sequence */
      continue;
    
    while ((t = strtok (NULL, " \t:")))
    {
      mh_read_token (t, &first, &last);
      for (; first <= last; first++)
	mhs_set (mhs, first, f);
    }
  }

  safe_free ((void **) &buff);
  safe_fclose (&fp);
}