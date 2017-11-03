static void pipe_attachment (FILE *fp, BODY *b, STATE *state)
{
  FILE *ifp;

  if (fp)
  {
    state->fpin = fp;
    mutt_decode_attachment (b, state);
    if (AttachSep)
      state_puts (AttachSep, state);
  }
  else
  {
    if ((ifp = fopen (b->filename, "r")) == NULL)
    {
      mutt_perror ("fopen");
      return;
    }
    mutt_copy_stream (ifp, state->fpout);
    safe_fclose (&ifp);
    if (AttachSep)
      state_puts (AttachSep, state);
  }
}