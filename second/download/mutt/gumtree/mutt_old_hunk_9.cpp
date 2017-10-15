  }

  if (!Pager || mutt_strcmp (Pager, "builtin") == 0)
    builtin = 1;
  else
  {
    mutt_make_string (buf, sizeof (buf), NONULL(PagerFmt), Context, cur);
    fputs (buf, fpout);
    fputs ("\n\n", fpout);
  }

  res = mutt_copy_message (fpout, Context, cur, cmflags,
       	(option (OPTWEED) ? (CH_WEED | CH_REORDER) : 0) | CH_DECODE | CH_FROM);
  if ((safe_fclose (&fpout) != 0 && errno != EPIPE) || res == -1)
  {
    mutt_error (_("Could not copy message"));
    if (fpfilterout != NULL)
    {
      mutt_wait_filter (filterpid);
      safe_fclose (&fpfilterout);
