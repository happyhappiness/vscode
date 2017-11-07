static void cmd_parse_fetch (IMAP_DATA* idata, char* s)
{
  int msgno, cur;
  HEADER* h = NULL;

  dprint (3, (debugfile, "Handling FETCH\n"));

  msgno = atoi (s);
  
  if (msgno <= idata->ctx->msgcount)
  /* see cmd_parse_expunge */
    for (cur = 0; cur < idata->ctx->msgcount; cur++)
    {
      h = idata->ctx->hdrs[cur];
      
      if (h && h->active && h->index+1 == msgno)
      {
	dprint (2, (debugfile, "Message UID %d updated\n", HEADER_DATA(h)->uid));
	break;
      }
      
      h = NULL;
    }
  
  if (!h)
  {
    dprint (3, (debugfile, "FETCH response ignored for this message\n"));
    return;
  }
  
  /* skip FETCH */
  s = imap_next_word (s);
  s = imap_next_word (s);

  if (*s != '(')
  {
    dprint (1, (debugfile, "Malformed FETCH response"));
    return;
  }
  s++;

  if (ascii_strncasecmp ("FLAGS", s, 5) != 0)
  {
    dprint (2, (debugfile, "Only handle FLAGS updates\n"));
    return;
  }

  /* If server flags could conflict with mutt's flags, reopen the mailbox. */
  if (h->changed)
    idata->reopen |= IMAP_EXPUNGE_PENDING;
  else {
    imap_set_flags (idata, h, s);
    idata->check_status = IMAP_FLAGS_PENDING;
  }
}