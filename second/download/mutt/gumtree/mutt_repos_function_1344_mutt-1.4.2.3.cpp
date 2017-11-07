static int browse_add_list_result (IMAP_DATA* idata, const char* cmd,
  struct browser_state* state, short isparent)
{
  char *name;
  int noselect;
  int noinferiors;
  IMAP_MBOX mx;

  if (imap_parse_path (state->folder, &mx))
  {
    dprint (2, (debugfile,
      "browse_add_list_result: current folder %s makes no sense\n", state->folder));
    return -1;
  }

  imap_cmd_start (idata, cmd);

  do 
  {
    if (imap_parse_list_response(idata, &name, &noselect, &noinferiors,
        &idata->delim) != 0)
    {
      FREE (&mx.mbox);
      return -1;
    }

    if (name)
    {
      /* Let a parent folder never be selectable for navigation */
      if (isparent)
        noselect = 1;
      /* prune current folder from output */
      if (isparent || mutt_strncmp (name, mx.mbox, strlen (name)))
        imap_add_folder (idata->delim, name, noselect, noinferiors, state,
          isparent);
    }
  }
  while ((ascii_strncmp (idata->cmd.buf, idata->cmd.seq, SEQLEN) != 0));

  FREE (&mx.mbox);
  return 0;
}