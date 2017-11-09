static void append_signature (FILE *f)
{
  FILE *tmpfp;
  pid_t thepid;

  if (Signature && (tmpfp = mutt_open_read (Signature, &thepid)))
  {
    if (option (OPTSIGDASHES))
      fputs ("\n-- \n", f);
    mutt_copy_stream (tmpfp, f);
    safe_fclose (&tmpfp);
    if (thepid != -1)
      mutt_wait_filter (thepid);
  }
}