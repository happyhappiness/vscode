int imap_browse (char* path, struct browser_state* state)
{
  IMAP_DATA* idata;
  char buf[LONG_STRING];
  char buf2[LONG_STRING];
  char nsbuf[LONG_STRING];
  char mbox[LONG_STRING];
  char list_cmd[5];
  IMAP_NAMESPACE_INFO nsi[16];
  int home_namespace = 0;
  int n;
  int i;
  int nsup;
  char ctmp;
  int nns;
  char *cur_folder;
  short showparents = 0;
  int noselect;
  int noinferiors;
  IMAP_MBOX mx;

  if (imap_parse_path (path, &mx))
  {
    mutt_error (_("%s is an invalid IMAP path"), path);
    return -1;
  }

  strfcpy (list_cmd, option (OPTIMAPLSUB) ? "LSUB" : "LIST", sizeof (list_cmd));

  if (!(idata = imap_conn_find (&(mx.account), 0)))
    goto fail;

  if (!mx.mbox)
  {
    home_namespace = 1;
    mbox[0] = '\0';		/* Do not replace "" with "INBOX" here */
    mx.mbox = safe_strdup(ImapHomeNamespace);
    nns = 0;
    if (mutt_bit_isset(idata->capabilities,NAMESPACE))
    {
      mutt_message _("Getting namespaces...");
      if (browse_get_namespace (idata, nsbuf, sizeof (nsbuf), 
			 nsi, sizeof (nsi),  &nns) != 0)
	goto fail;
      if (browse_verify_namespace (idata, nsi, nns) != 0)
	goto fail;
    }
  }

  mutt_message _("Getting folder list...");

  /* skip check for parents when at the root */
  if (mx.mbox && mx.mbox[0] != '\0')
  {
    imap_fix_path (idata, mx.mbox, mbox, sizeof (mbox));
    imap_munge_mbox_name (buf, sizeof (buf), mbox);
    imap_unquote_string(buf); /* As kludgy as it gets */
    mbox[sizeof (mbox) - 1] = '\0';
    strncpy (mbox, buf, sizeof (mbox) - 1);
    n = mutt_strlen (mbox);

    dprint (3, (debugfile, "imap_browse: mbox: %s\n", mbox));

    /* if our target exists and has inferiors, enter it if we
     * aren't already going to */
    if (mbox[n-1] != idata->delim)
    {
      snprintf (buf, sizeof (buf), "%s \"\" \"%s\"", list_cmd, mbox);
      imap_cmd_start (idata, buf);
      do 
      {
        if (imap_parse_list_response (idata, &cur_folder, &noselect,
            &noinferiors, &idata->delim) != 0)
	  goto fail;

        if (cur_folder)
        {
          imap_unmunge_mbox_name (cur_folder);

          if (!noinferiors && cur_folder[0] &&
            (n = strlen (mbox)) < LONG_STRING-1)
          {
            mbox[n++] = idata->delim;
            mbox[n] = '\0';
          }
        }
      }
      while (ascii_strncmp (idata->cmd.buf, idata->cmd.seq, SEQLEN));
    }

    /* if we're descending a folder, mark it as current in browser_state */
    if (mbox[n-1] == idata->delim)
    {
      /* don't show parents in the home namespace */
      if (!home_namespace)
	showparents = 1;
      imap_qualify_path (buf, sizeof (buf), &mx, mbox);
      state->folder = safe_strdup (buf);
      n--;
    }

    /* Find superiors to list
     * Note: UW-IMAP servers return folder + delimiter when asked to list
     *  folder + delimiter. Cyrus servers don't. So we ask for folder,
     *  and tack on delimiter ourselves.
     * Further note: UW-IMAP servers return nothing when asked for 
     *  NAMESPACES without delimiters at the end. Argh! */
    for (n--; n >= 0 && mbox[n] != idata->delim ; n--);
    if (n > 0)			/* "aaaa/bbbb/" -> "aaaa" */
    {
      /* forget the check, it is too delicate (see above). Have we ever
       * had the parent not exist? */
      ctmp = mbox[n];
      mbox[n] = '\0';

      if (showparents)
      {
	dprint (3, (debugfile, "imap_init_browse: adding parent %s\n", mbox));
	imap_add_folder (idata->delim, mbox, 1, 0, state, 1);
      }

      /* if our target isn't a folder, we are in our superior */
      if (!state->folder)
      {
        /* store folder with delimiter */
        mbox[n++] = ctmp;
        ctmp = mbox[n];
        mbox[n] = '\0';
        imap_qualify_path (buf, sizeof (buf), &mx, mbox);
        state->folder = safe_strdup (buf);
      }
      mbox[n] = ctmp;
    } 
    /* "/bbbb/" -> add  "/", "aaaa/" -> add "" */
    else
    {
      char relpath[2];
      /* folder may be "/" */
      snprintf (relpath, sizeof (relpath), "%c" , n < 0 ? '\0' : idata->delim);
      if (showparents)
        imap_add_folder (idata->delim, relpath, 1, 0, state, 1); 
      if (!state->folder)
      {
        imap_qualify_path (buf, sizeof (buf), &mx, relpath);
        state->folder = safe_strdup (buf);
      }
    }
  }

  /* no namespace, no folder: set folder to host only */
  if (!state->folder)
  {
    imap_qualify_path (buf, sizeof (buf), &mx, NULL);
    state->folder = safe_strdup (buf);
  }

  if (home_namespace && mbox[0] != '\0')
  {
    /* Listing the home namespace, so INBOX should be included. Home 
     * namespace is not "", so we have to list it explicitly. We ask the 
     * server to see if it has descendants. */
    dprint (3, (debugfile, "imap_browse: adding INBOX\n"));
    if (browse_add_list_result (idata, "LIST \"\" \"INBOX\"", state, 0))
      goto fail;
  }

  nsup = state->entrylen;

  dprint (3, (debugfile, "imap_browse: Quoting mailbox scan: %s -> ", mbox));
  snprintf (buf, sizeof (buf), "%s%%", mbox);
  imap_quote_string (buf2, sizeof (buf2), buf);
  dprint (3, (debugfile, "%s\n", buf2));
  snprintf (buf, sizeof (buf), "%s \"\" %s", list_cmd, buf2);
  if (browse_add_list_result (idata, buf, state, 0))
    goto fail;

  if (!state->entrylen)
  {
    mutt_error _("No such folder");
    goto fail;
  }

  mutt_clear_error ();

  qsort(&(state->entry[nsup]),state->entrylen-nsup,sizeof(state->entry[0]),
	(int (*)(const void*,const void*)) compare_names);
  if (home_namespace)
  {				/* List additional namespaces */
    for (i = 0; i < nns; i++)
      if (nsi[i].listable && !nsi[i].home_namespace) {
	imap_add_folder(nsi[i].delim, nsi[i].prefix, nsi[i].noselect,
			nsi[i].noinferiors, state, 0);
	dprint (3, (debugfile, "imap_browse: adding namespace: %s\n",
		    nsi[i].prefix));
      }
  }

  FREE (&mx.mbox);
  return 0;

 fail:
  FREE (&mx.mbox);
  return -1;
}