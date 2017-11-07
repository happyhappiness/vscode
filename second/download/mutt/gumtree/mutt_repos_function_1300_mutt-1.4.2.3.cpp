int imap_open_mailbox (CONTEXT* ctx)
{
  CONNECTION *conn;
  IMAP_DATA *idata;
  char buf[LONG_STRING];
  char bufout[LONG_STRING];
  int count = 0;
  IMAP_MBOX mx;
  int rc;
  
  if (imap_parse_path (ctx->path, &mx))
  {
    mutt_error (_("%s is an invalid IMAP path"), ctx->path);
    return -1;
  }

  /* we require a connection which isn't currently in IMAP_SELECTED state */
  if (!(idata = imap_conn_find (&(mx.account), M_IMAP_CONN_NOSELECT)))
    goto fail_noidata;
  conn = idata->conn;

  /* once again the context is new */
  ctx->data = idata;

  if (idata->status == IMAP_FATAL)
    goto fail;

  /* Clean up path and replace the one in the ctx */
  imap_fix_path (idata, mx.mbox, buf, sizeof (buf));
  FREE(&(idata->mailbox));
  idata->mailbox = safe_strdup (buf);
  imap_qualify_path (buf, sizeof (buf), &mx, idata->mailbox);

  FREE (&(ctx->path));
  ctx->path = safe_strdup (buf);

  idata->ctx = ctx;

  /* clear mailbox status */
  idata->status = 0;
  memset (idata->rights, 0, (RIGHTSMAX+7)/8);
  idata->newMailCount = 0;

  mutt_message (_("Selecting %s..."), idata->mailbox);
  imap_munge_mbox_name (buf, sizeof(buf), idata->mailbox);
  snprintf (bufout, sizeof (bufout), "%s %s",
    ctx->readonly ? "EXAMINE" : "SELECT", buf);

  idata->state = IMAP_SELECTED;

  imap_cmd_start (idata, bufout);

  do
  {
    char *pc;
    
    if ((rc = imap_cmd_step (idata)) != IMAP_CMD_CONTINUE)
      break;

    pc = idata->cmd.buf + 2;

    /* Obtain list of available flags here, may be overridden by a
     * PERMANENTFLAGS tag in the OK response */
    if (ascii_strncasecmp ("FLAGS", pc, 5) == 0)
    {
      /* don't override PERMANENTFLAGS */
      if (!idata->flags)
      {
	dprint (2, (debugfile, "Getting mailbox FLAGS\n"));
	if ((pc = imap_get_flags (&(idata->flags), pc)) == NULL)
	  goto fail;
      }
    }
    /* PERMANENTFLAGS are massaged to look like FLAGS, then override FLAGS */
    else if (ascii_strncasecmp ("OK [PERMANENTFLAGS", pc, 18) == 0)
    {
      dprint (2, (debugfile, "Getting mailbox PERMANENTFLAGS\n"));
      /* safe to call on NULL */
      mutt_free_list (&(idata->flags));
      /* skip "OK [PERMANENT" so syntax is the same as FLAGS */
      pc += 13;
      if ((pc = imap_get_flags (&(idata->flags), pc)) == NULL)
	goto fail;
    }
    else
    {
      pc = imap_next_word (pc);
      if (!ascii_strncasecmp ("EXISTS", pc, 6))
      {
	count = idata->newMailCount;
	idata->newMailCount = 0;
      }
    }
  }
  while (rc == IMAP_CMD_CONTINUE);

  if (rc == IMAP_CMD_NO)
  {
    char *s;
    s = imap_next_word (idata->cmd.buf); /* skip seq */
    s = imap_next_word (s); /* Skip response */
    mutt_error ("%s", s);
    mutt_sleep (2);
    goto fail;
  }

  if (rc != IMAP_CMD_OK)
    goto fail;

  /* check for READ-ONLY notification */
  if (!ascii_strncasecmp (imap_get_qualifier (idata->cmd.buf), "[READ-ONLY]", 11))
  {
    dprint (2, (debugfile, "Mailbox is read-only.\n"));
    ctx->readonly = 1;
  }

#ifdef DEBUG
  /* dump the mailbox flags we've found */
  if (debuglevel > 2)
  {
    if (!idata->flags)
      dprint (3, (debugfile, "No folder flags found\n"));
    else
    {
      LIST* t = idata->flags;

      dprint (3, (debugfile, "Mailbox flags: "));

      t = t->next;
      while (t)
      {
        dprint (3, (debugfile, "[%s] ", t->data));
        t = t->next;
      }
      dprint (3, (debugfile, "\n"));
    }
  }
#endif

  if (mutt_bit_isset (idata->capabilities, ACL))
  {
    if (imap_check_acl (idata))
      goto fail;
  }
  /* assume we have all rights if ACL is unavailable */
  else
  {
    mutt_bit_set (idata->rights, IMAP_ACL_LOOKUP);
    mutt_bit_set (idata->rights, IMAP_ACL_READ);
    mutt_bit_set (idata->rights, IMAP_ACL_SEEN);
    mutt_bit_set (idata->rights, IMAP_ACL_WRITE);
    mutt_bit_set (idata->rights, IMAP_ACL_INSERT);
    mutt_bit_set (idata->rights, IMAP_ACL_POST);
    mutt_bit_set (idata->rights, IMAP_ACL_CREATE);
    mutt_bit_set (idata->rights, IMAP_ACL_DELETE);
  }

  ctx->hdrmax = count;
  ctx->hdrs = safe_malloc (count * sizeof (HEADER *));
  ctx->v2r = safe_malloc (count * sizeof (int));
  ctx->msgcount = 0;
  if (count && (imap_read_headers (idata, 0, count-1) < 0))
  {
    mutt_error _("Error opening mailbox");
    mutt_sleep (1);
    goto fail;
  }

  dprint (2, (debugfile, "imap_open_mailbox: msgcount is %d\n", ctx->msgcount));
  FREE (&mx.mbox);
  return 0;

 fail:
  idata->state = IMAP_AUTHENTICATED;
 fail_noidata:
  FREE (&mx.mbox);
  return -1;
}