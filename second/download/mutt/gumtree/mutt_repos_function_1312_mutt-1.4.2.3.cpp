int imap_complete(char* dest, size_t dlen, char* path) {
  CONNECTION* conn;
  IMAP_DATA* idata;
  char list[LONG_STRING];
  char buf[LONG_STRING];
  char* list_word = NULL;
  int noselect, noinferiors;
  char delim;
  char completion[LONG_STRING];
  int clen, matchlen = 0;
  int completions = 0;
  int pos = 0;
  IMAP_MBOX mx;

  /* verify passed in path is an IMAP path */
  if (imap_parse_path (path, &mx))
  {
    dprint(2, (debugfile, "imap_complete: bad path %s\n", path));
    return -1;
  }

  /* don't open a new socket just for completion */
  if (!(idata = imap_conn_find (&(mx.account), M_IMAP_CONN_NONEW)))
    goto fail;
  conn = idata->conn;

  /* reformat path for IMAP list, and append wildcard */
  /* don't use INBOX in place of "" */
  if (mx.mbox && mx.mbox[0])
    imap_fix_path (idata, mx.mbox, list, sizeof(list));
  else
    list[0] = '\0';

  /* fire off command */
  snprintf (buf, sizeof(buf), "%s \"\" \"%s%%\"",
    option (OPTIMAPLSUB) ? "LSUB" : "LIST", list);

  imap_cmd_start (idata, buf);

  /* and see what the results are */
  strfcpy (completion, NONULL(mx.mbox), sizeof(completion));
  do
  {
    if (imap_parse_list_response(idata, &list_word, &noselect, &noinferiors,
        &delim))
      break;

    if (list_word)
    {
      /* store unquoted */
      imap_unmunge_mbox_name (list_word);

      /* if the folder isn't selectable, append delimiter to force browse
       * to enter it on second tab. */
      if (noselect)
      {
        clen = strlen(list_word);
        list_word[clen++] = delim;
        list_word[clen] = '\0';
      }
      /* copy in first word */
      if (!completions)
      {
        strfcpy (completion, list_word, sizeof(completion));
        matchlen = strlen (completion);
        completions++;
        continue;
      }

      pos = 0;
      while (pos < matchlen && list_word[pos] &&
          completion[pos] == list_word[pos])
        pos++;
      completion[pos] = '\0';
      matchlen = pos;

      completions++;
    }
  }
  while (ascii_strncmp(idata->cmd.seq, idata->cmd.buf, SEQLEN));

  if (completions)
  {
    /* reformat output */
    imap_qualify_path (dest, dlen, &mx, completion);
    mutt_pretty_mailbox (dest);

    FREE (&mx.mbox);
    return 0;
  }

 fail:
  FREE (&mx.mbox);
  return -1;
}