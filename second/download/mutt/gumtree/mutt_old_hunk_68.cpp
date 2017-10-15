  mhs->flags[i] &= ~f;
  return mhs->flags[i];
}

#endif

static void mh_read_token (char *t, int *first, int *last)
{
  char *p;
  if ((p = strchr (t, '-')))
  {
    *p++ = '\0';
    *first = atoi (t);
    *last  = atoi (p);
  }
  else
    *first = *last = atoi (t);
}

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

int mh_buffy (const char *path)
{
  int i, r = 0;
  struct mh_sequences mhs;
  memset (&mhs, 0, sizeof (mhs));
  
  mh_read_sequences (&mhs, path);
  for (i = 0; !r && i <= mhs.max; i++)
    if (mhs_check (&mhs, i) & MH_SEQ_UNSEEN)
      r = 1;
  mhs_free_sequences (&mhs);
  return r;
}

static int mh_mkstemp (CONTEXT *dest, FILE **fp, char **tgt)
{
  int fd;
  char path[_POSIX_PATH_MAX];

  FOREVER 
  {
    snprintf (path, _POSIX_PATH_MAX, "%s/.mutt-%s-%d-%d",
	      dest->path, NONULL (Hostname), (int) getpid (), Counter++);
    if ((fd = open (path, O_WRONLY | O_EXCL | O_CREAT, 0600)) == -1)
    {
      if (errno != EEXIST)
      {
	mutt_perror (path);
	return -1;
      }
    }
    else
    {
      *tgt = safe_strdup (path);
      break;
    }
  }

  if ((*fp = fdopen (fd, "w")) == NULL)
  {
    FREE (tgt);
    close (fd);
    unlink (path);
    return (-1);
  }
  
  return 0;
}

static void mhs_write_one_sequence (FILE *fp, struct mh_sequences *mhs,
				    short f, const char *tag)
{
  int i;
  int first, last;
  fprintf (fp, "%s:", tag);
  
  first = -1;
  last  = -1;
  
  for (i = 0; i <= mhs->max; i++)
  {
    if ((mhs_check (mhs, i) & f))
    {
      if (first < 0)
	first = i;
