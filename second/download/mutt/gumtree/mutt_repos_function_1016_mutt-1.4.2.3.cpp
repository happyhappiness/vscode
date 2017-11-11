static void mh_sequences_add_one (CONTEXT *ctx, int n, short unseen, short flagged, short replied)
{
  short unseen_done = 0;
  short flagged_done = 0;
  short replied_done = 0;
  
  FILE *ofp = NULL, *nfp = NULL;
 
  char *tmpfname;
  char sequences[_POSIX_PATH_MAX];

  char seq_unseen[STRING];
  char seq_replied[STRING];
  char seq_flagged[STRING];
  
  char *buff = NULL;
  int line;
  size_t sz;
  
  if (mh_mkstemp (ctx, &nfp, &tmpfname) == -1)
    return;

  snprintf (seq_unseen, sizeof (seq_unseen), "%s:", NONULL (MhUnseen));
  snprintf (seq_replied, sizeof (seq_replied), "%s:", NONULL (MhReplied));
  snprintf (seq_flagged, sizeof (seq_flagged), "%s:", NONULL (MhFlagged));
  
  snprintf (sequences, sizeof (sequences), "%s/.mh_sequences", ctx->path);
  if ((ofp = fopen (sequences, "r")))
  {
    while ((buff = mutt_read_line (buff, &sz, ofp, &line)))
    {
      if (unseen && !strncmp (buff, seq_unseen, mutt_strlen (seq_unseen)))
      {
	fprintf (nfp, "%s %d\n", buff, n);
	unseen_done = 1;
      }
      else if (flagged && !strncmp (buff, seq_flagged, mutt_strlen (seq_flagged)))
      {
	fprintf (nfp, "%s %d\n", buff, n);
	flagged_done = 1;
      }
      else if (replied && !strncmp (buff, seq_replied, mutt_strlen (seq_replied)))
      {
	fprintf (nfp, "%s %d\n", buff, n);
	replied_done = 1;
      }
      else
	fprintf (nfp, "%s\n", buff);
    }
  }
  safe_fclose (&ofp);
  safe_free ((void **) &buff);
  
  if (!unseen_done  && unseen)   fprintf (nfp, "%s: %d\n", NONULL (MhUnseen), n);
  if (!flagged_done && flagged)  fprintf (nfp, "%s: %d\n", NONULL (MhFlagged), n);
  if (!replied_done && replied)  fprintf (nfp, "%s: %d\n", NONULL (MhReplied), n);
  
  safe_fclose (&nfp);
  
  unlink (sequences);
  if (safe_rename (tmpfname, sequences) != 0)
    unlink (tmpfname);
  
  safe_free ((void **) &tmpfname);
}