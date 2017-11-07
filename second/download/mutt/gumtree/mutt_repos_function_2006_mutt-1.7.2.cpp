int imap_browse (char* path, struct browser_state* state)
{
  IMAP_DATA* idata;
  IMAP_LIST list;
  char buf[LONG_STRING];
  char mbox[LONG_STRING];
  char munged_mbox[LONG_STRING];
  char list_cmd[5];
  int n;
  int nsup;
  char ctmp;
  short showparents = 0;
  int save_lsub;
  IMAP_MBOX mx;

  if (imap_parse_path (path, &mx))
  {
    mutt_error (_("%s is an invalid IMAP path"), path);
    return -1;
  }

  save_lsub = option (OPTIMAPCHECKSUBSCRIBED);
  unset_option (OPTIMAPCHECKSUBSCRIBED);
  strfcpy (list_cmd, option (OPTIMAPLSUB) ? "LSUB" : "LIST", sizeof (list_cmd));

  if (!(idata = imap_conn_find (&(mx.account), 0)))
    goto fail;

  mutt_message _("Getting folder list...");

  /* skip check for parents when at the root */
  if (mx.mbox && mx.mbox[0] != '\0')
  {
    imap_fix_path (idata, mx.mbox, mbox, sizeof (mbox));
    n = mutt_strlen (mbox);
  }
  else
  {
    mbox[0] = '\0';
    n = 0;
  }

  if (n)
  {
    int rc;
    dprint (3, (debugfile, "imap_browse: mbox: %s\n", mbox));

    /* if our target exists and has inferiors, enter it if we
     * aren't already going to */
    imap_munge_mbox_name (idata, munged_mbox, sizeof (munged_mbox), mbox);
    snprintf (buf, sizeof (buf), "%s \"\" %s", list_cmd, munged_mbox);
    imap_cmd_start (idata, buf);
    idata->cmdtype = IMAP_CT_LIST;
    idata->cmddata = &list;
    do
    {
      list.name = 0;
      rc = imap_cmd_step (idata);
      if (rc == IMAP_CMD_CONTINUE && list.name)
      {
        if (!list.noinferiors && list.name[0] &&
            !imap_mxcmp (list.name, mbox) &&
            n < sizeof (mbox) - 1)
        {
          mbox[n++] = list.delim;
          mbox[n] = '\0';
        }
      }
    }
    while (rc == IMAP_CMD_CONTINUE);
    idata->cmddata = NULL;

    /* if we're descending a folder, mark it as current in browser_state */
    if (mbox[n-1] == list.delim)
    {
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
    for (n--; n >= 0 && mbox[n] != list.delim ; n--);
    if (n > 0)			/* "aaaa/bbbb/" -> "aaaa" */
    {
      /* forget the check, it is too delicate (see above). Have we ever
       * had the parent not exist? */
      ctmp = mbox[n];
      mbox[n] = '\0';

      if (showparents)
      {
	dprint (3, (debugfile, "imap_init_browse: adding parent %s\n", mbox));
	imap_add_folder (list.delim, mbox, 1, 0, state, 1);
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

  nsup = state->entrylen;

  dprint (3, (debugfile, "imap_browse: Quoting mailbox scan: %s -> ", mbox));
  snprintf (buf, sizeof (buf), "%s%%", mbox);
  imap_munge_mbox_name (idata, munged_mbox, sizeof (munged_mbox), buf);
  dprint (3, (debugfile, "%s\n", munged_mbox));
  snprintf (buf, sizeof (buf), "%s \"\" %s", list_cmd, munged_mbox);
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

  if (save_lsub)
    set_option (OPTIMAPCHECKSUBSCRIBED);

  FREE (&mx.mbox);
  return 0;

 fail:
  if (save_lsub)
    set_option (OPTIMAPCHECKSUBSCRIBED);
  FREE (&mx.mbox);
  return -1;
}