    else if (first >= 0)
    {
      if (last < 0)
	fprintf (fp, " %d", first);
      else
	fprintf (fp, " %d-%d", first, last);

      first = -1;
      last = -1;
    }
  }

  if (first >= 0)
  {
    if (last < 0)
      fprintf (fp, " %d", first);
    else
      fprintf (fp, " %d-%d", first, last);
  }

  fputc ('\n', fp);
}

/* XXX - we don't currently remove deleted messages from sequences we don't know.  Should we? */

static void mh_update_sequences (CONTEXT * ctx)
{
  FILE *ofp, *nfp;

  char sequences[_POSIX_PATH_MAX];
  char *tmpfname;
  char *buff = NULL;
  char *p;
  size_t s;
  int l = 0;
  int i;

  int unseen = 0;
  int flagged = 0;
  int replied = 0;

  char seq_unseen[STRING];
  char seq_replied[STRING];
  char seq_flagged[STRING];


  struct mh_sequences mhs;
  memset (&mhs, 0, sizeof (mhs));

  snprintf (seq_unseen, sizeof (seq_unseen), "%s:", NONULL (MhUnseen));
  snprintf (seq_replied, sizeof (seq_replied), "%s:", NONULL (MhReplied));
  snprintf (seq_flagged, sizeof (seq_flagged), "%s:", NONULL (MhFlagged));

  if (mh_mkstemp (ctx, &nfp, &tmpfname) != 0)
  {
    /* error message? */
    return;
  }

  snprintf (sequences, sizeof (sequences), "%s/.mh_sequences", ctx->path);


  /* first, copy unknown sequences */
  if ((ofp = fopen (sequences, "r")))
  {
    while ((buff = mutt_read_line (buff, &s, ofp, &l, 0)))
    {
      if (!mutt_strncmp (buff, seq_unseen, mutt_strlen (seq_unseen)))
	continue;
      if (!mutt_strncmp (buff, seq_flagged, mutt_strlen (seq_flagged)))
	continue;
      if (!mutt_strncmp (buff, seq_replied, mutt_strlen (seq_replied)))
	continue;

      fprintf (nfp, "%s\n", buff);
    }
  }
  safe_fclose (&ofp);

  /* now, update our unseen, flagged, and replied sequences */
  for (l = 0; l < ctx->msgcount; l++)
  {
    if (ctx->hdrs[l]->deleted)
      continue;

    if ((p = strrchr (ctx->hdrs[l]->path, '/')))
      p++;
    else
      p = ctx->hdrs[l]->path;

    if (mutt_atoi (p, &i) < 0)
      continue;

    if (!ctx->hdrs[l]->read)
    {
      mhs_set (&mhs, i, MH_SEQ_UNSEEN);
      unseen++;
    }
    if (ctx->hdrs[l]->flagged)
