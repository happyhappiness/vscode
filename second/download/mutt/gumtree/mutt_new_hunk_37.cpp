
  dprint (2, (debugfile, "imap_open_mailbox: msgcount is %d\n", ctx->msgcount));
  FREE (&mx.mbox);
  return 0;

 fail:
  if (idata->state == IMAP_SELECTED)
    idata->state = IMAP_AUTHENTICATED;
 fail_noidata:
  FREE (&mx.mbox);
  return -1;
}

int imap_open_mailbox_append (CONTEXT *ctx)
{
  IMAP_DATA *idata;
  char buf[LONG_STRING];
  char mailbox[LONG_STRING];
  IMAP_MBOX mx;
  int rc;

  if (imap_parse_path (ctx->path, &mx))
    return -1;

  /* in APPEND mode, we appear to hijack an existing IMAP connection -
   * ctx is brand new and mostly empty */

  if (!(idata = imap_conn_find (&(mx.account), 0)))
  {
    FREE (&mx.mbox);
    return -1;
  }

  ctx->magic = M_IMAP;
  ctx->data = idata;

  imap_fix_path (idata, mx.mbox, mailbox, sizeof (mailbox));
  if (!*mailbox)
    strfcpy (mailbox, "INBOX", sizeof (mailbox));
  FREE (&mx.mbox);

  /* really we should also check for W_OK */
  if ((rc = imap_access (ctx->path, F_OK)) == 0)
    return 0;

  if (rc == -1)
    return -1;

  snprintf (buf, sizeof (buf), _("Create %s?"), mailbox);
  if (option (OPTCONFIRMCREATE) && mutt_yesorno (buf, 1) < 1)
    return -1;

  if (imap_create_mailbox (idata, mailbox) < 0)
    return -1;

  return 0;
}

/* imap_logout: Gracefully log out of server. */
void imap_logout (IMAP_DATA** idata)
{
  /* we set status here to let imap_handle_untagged know we _expect_ to
   * receive a bye response (so it doesn't freak out and close the conn) */
  (*idata)->status = IMAP_BYE;
  imap_cmd_start (*idata, "LOGOUT");
  while (imap_cmd_step (*idata) == IMAP_CMD_CONTINUE)
    ;

  mutt_socket_close ((*idata)->conn);
  imap_free_idata (idata);
}

/* imap_set_flag: append str to flags if we currently have permission
 *   according to aclbit */
static void imap_set_flag (IMAP_DATA* idata, int aclbit, int flag,
  const char *str, char *flags, size_t flsize)
{
  if (mutt_bit_isset (idata->ctx->rights, aclbit))
    if (flag && imap_has_flag (idata->flags, str))
      safe_strcat (flags, flsize, str);
}

/* imap_has_flag: do a caseless comparison of the flag against a flag list,
*   return 1 if found or flag list has '\*', 0 otherwise */
int imap_has_flag (LIST* flag_list, const char* flag)
{
  if (!flag_list)
    return 0;

  flag_list = flag_list->next;
  while (flag_list)
  {
    if (!ascii_strncasecmp (flag_list->data, flag, strlen (flag_list->data)))
      return 1;

    if (!ascii_strncmp (flag_list->data, "\\*", strlen (flag_list->data)))
      return 1;

    flag_list = flag_list->next;
  }

  return 0;
}

/* Note: headers must be in SORT_ORDER. See imap_exec_msgset for args.
 * Pos is an opaque pointer a la strtok. It should be 0 at first call. */
static int imap_make_msg_set (IMAP_DATA* idata, BUFFER* buf, int flag,
                              int changed, int invert, int* pos)
{
  HEADER** hdrs = idata->ctx->hdrs;
  int count = 0;	/* number of messages in message set */
  int match = 0;	/* whether current message matches flag condition */
  unsigned int setstart = 0;	/* start of current message range */
  int n;
  int started = 0;

  hdrs = idata->ctx->hdrs;

  for (n = *pos;
       n < idata->ctx->msgcount && buf->dptr - buf->data < IMAP_MAX_CMDLEN;
       n++)
  {
    match = 0;
    /* don't include pending expunged messages */
    if (hdrs[n]->active)
      switch (flag)
      {
        case M_DELETED:
          if (hdrs[n]->deleted != HEADER_DATA(hdrs[n])->deleted)
            match = invert ^ hdrs[n]->deleted;
	  break;
        case M_FLAG:
          if (hdrs[n]->flagged != HEADER_DATA(hdrs[n])->flagged)
            match = invert ^ hdrs[n]->flagged;
	  break;
        case M_OLD:
          if (hdrs[n]->old != HEADER_DATA(hdrs[n])->old)
            match = invert ^ hdrs[n]->old;
	  break;
        case M_READ:
          if (hdrs[n]->read != HEADER_DATA(hdrs[n])->read)
            match = invert ^ hdrs[n]->read;
	  break;
        case M_REPLIED:
          if (hdrs[n]->replied != HEADER_DATA(hdrs[n])->replied)
            match = invert ^ hdrs[n]->replied;
	  break;

        case M_TAG:
	  if (hdrs[n]->tagged)
	    match = 1;
	  break;
      }

