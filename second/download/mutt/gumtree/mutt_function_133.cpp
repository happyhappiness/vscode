int mutt_view_attachment (FILE *fp, BODY *a, int flag, HEADER *hdr,
			  ATTACHPTR **idx, short idxlen)
{
  char tempfile[_POSIX_PATH_MAX] = "";
  char pagerfile[_POSIX_PATH_MAX] = "";
  int is_message;
  int use_mailcap;
  int use_pipe = 0;
  int use_pager = 1;
  char type[STRING];
  char command[HUGE_STRING];
  char descrip[STRING];
  char *fname;
  rfc1524_entry *entry = NULL;
  int rc = -1;
  int unlink_tempfile = 0;
  
  is_message = mutt_is_message_type(a->type, a->subtype);
  if (WithCrypto && is_message && a->hdr && (a->hdr->security & ENCRYPT) &&
      !crypt_valid_passphrase(a->hdr->security))
    return (rc);
  use_mailcap = (flag == M_MAILCAP ||
		(flag == M_REGULAR && mutt_needs_mailcap (a)));
  snprintf (type, sizeof (type), "%s/%s", TYPE (a), a->subtype);
  
  if (use_mailcap)
  {
    entry = rfc1524_new_entry (); 
    if (!rfc1524_mailcap_lookup (a, type, entry, 0))
    {
      if (flag == M_REGULAR)
      {
	/* fallback to view as text */
	rfc1524_free_entry (&entry);
	mutt_error _("No matching mailcap entry found.  Viewing as text.");
	flag = M_AS_TEXT;
	use_mailcap = 0;
      }
      else
	goto return_error;
    }
  }
  
  if (use_mailcap)
  {
    if (!entry->command)
    {
      mutt_error _("MIME type not defined.  Cannot view attachment.");
      goto return_error;
    }
    strfcpy (command, entry->command, sizeof (command));
    
    if (fp)
    {
      fname = safe_strdup (a->filename);
      mutt_sanitize_filename (fname, 1);
    }
    else
      fname = a->filename;

    if (rfc1524_expand_filename (entry->nametemplate, fname,
				 tempfile, sizeof (tempfile)))
    {
      if (fp == NULL && mutt_strcmp(tempfile, a->filename))
      {
	/* send case: the file is already there */
	if (safe_symlink (a->filename, tempfile) == -1)
	{
	  if (mutt_yesorno (_("Can't match nametemplate, continue?"), M_YES) == M_YES)
	    strfcpy (tempfile, a->filename, sizeof (tempfile));
	  else
	    goto return_error;
	}
	else
	  unlink_tempfile = 1;
      }
    }
    else if (fp == NULL) /* send case */
      strfcpy (tempfile, a->filename, sizeof (tempfile));
    
    if (fp)
    {
      /* recv case: we need to save the attachment to a file */
      FREE (&fname);
      if (mutt_save_attachment (fp, a, tempfile, 0, NULL) == -1)
	goto return_error;
    }

    use_pipe = rfc1524_expand_command (a, tempfile, type,
				       command, sizeof (command));
    use_pager = entry->copiousoutput;
  }
  
  if (use_pager)
  {
    if (fp && !use_mailcap && a->filename)
    {
      /* recv case */
      strfcpy (pagerfile, a->filename, sizeof (pagerfile));
      mutt_adv_mktemp (pagerfile, sizeof(pagerfile));
    }
    else
      mutt_mktemp (pagerfile, sizeof (pagerfile));
  }
    
  if (use_mailcap)
  {
    pid_t thepid = 0;
    int tempfd = -1, pagerfd = -1;
    
    if (!use_pager)
      mutt_endwin (NULL);

    if (use_pager || use_pipe)
    {
      if (use_pager && ((pagerfd = safe_open (pagerfile, O_CREAT | O_EXCL | O_WRONLY)) == -1))
      {
	mutt_perror ("open");
	goto return_error;
      }
      if (use_pipe && ((tempfd = open (tempfile, 0)) == -1))
      {
	if(pagerfd != -1)
	  close(pagerfd);
	mutt_perror ("open");
	goto return_error;
      }

      if ((thepid = mutt_create_filter_fd (command, NULL, NULL, NULL,
					   use_pipe ? tempfd : -1, use_pager ? pagerfd : -1, -1)) == -1)
      {
	if(pagerfd != -1)
	  close(pagerfd);
	
	if(tempfd != -1)
	  close(tempfd);

	mutt_error _("Cannot create filter");
	goto return_error;
      }

      if (use_pager)
      {
	if (a->description)
	  snprintf (descrip, sizeof (descrip),
		    _("---Command: %-20.20s Description: %s"),
		    command, a->description);
	else
	  snprintf (descrip, sizeof (descrip),
		    _("---Command: %-30.30s Attachment: %s"), command, type);
      }

      if ((mutt_wait_filter (thepid) || (entry->needsterminal &&
	  option (OPTWAITKEY))) && !use_pager)
	mutt_any_key_to_continue (NULL);

      if (tempfd != -1)
	close (tempfd);
      if (pagerfd != -1)
	close (pagerfd);
    }
    else
    {
      /* interactive command */
      if (mutt_system (command) ||
	  (entry->needsterminal && option (OPTWAITKEY)))
	mutt_any_key_to_continue (NULL);
    }
  }
  else
  {
    /* Don't use mailcap; the attachment is viewed in the pager */

    if (flag == M_AS_TEXT)
    {
      /* just let me see the raw data */
      if (fp)
      {
	/* Viewing from a received message.
	 *
	 * Don't use mutt_save_attachment() because we want to perform charset
	 * conversion since this will be displayed by the internal pager.
	 */
	STATE decode_state;

	memset(&decode_state, 0, sizeof(decode_state));
	decode_state.fpout = safe_fopen(pagerfile, "w");
	if (!decode_state.fpout)
	{
	  dprint(1, (debugfile, "mutt_view_attachment:%d safe_fopen(%s) errno=%d %s\n", __LINE__, pagerfile, errno, strerror(errno)));
	  mutt_perror(pagerfile);
	  mutt_sleep(1);
	  goto return_error;
	}
	decode_state.fpin = fp;
	decode_state.flags = M_CHARCONV;
	mutt_decode_attachment(a, &decode_state);
	if (fclose(decode_state.fpout) == EOF)
	  dprint(1, (debugfile, "mutt_view_attachment:%d fclose errno=%d %s\n", __LINE__, pagerfile, errno, strerror(errno)));
      }
      else
      {
	/* in compose mode, just copy the file.  we can't use
	 * mutt_decode_attachment() since it assumes the content-encoding has
	 * already been applied
	 */
	if (mutt_save_attachment(fp, a, pagerfile, 0, NULL))
	  goto return_error;
      }
    }
    else
    {
      /* Use built-in handler */
      set_option (OPTVIEWATTACH); /* disable the "use 'v' to view this part"
				   * message in case of error */
      if (mutt_decode_save_attachment (fp, a, pagerfile, M_DISPLAY, 0))
      {
	unset_option (OPTVIEWATTACH);
	goto return_error;
      }
      unset_option (OPTVIEWATTACH);
    }
    
    if (a->description)
      strfcpy (descrip, a->description, sizeof (descrip));
    else if (a->filename)
      snprintf (descrip, sizeof (descrip), _("---Attachment: %s: %s"),
	  a->filename, type);
    else
      snprintf (descrip, sizeof (descrip), _("---Attachment: %s"), type);
  }
  
  /* We only reach this point if there have been no errors */

  if (use_pager)
  {
    pager_t info;
    
    memset (&info, 0, sizeof (info));
    info.fp = fp;
    info.bdy = a;
    info.ctx = Context;
    info.idx = idx;
    info.idxlen = idxlen;
    info.hdr = hdr;

    rc = mutt_do_pager (descrip, pagerfile,
			M_PAGER_ATTACHMENT | (is_message ? M_PAGER_MESSAGE : 0), &info);
    *pagerfile = '\0';
  }
  else
    rc = 0;

  return_error:
  
  if (entry)
    rfc1524_free_entry (&entry);
  if (fp && tempfile[0])
    mutt_unlink (tempfile);
  else if (unlink_tempfile)
    unlink(tempfile);

  if (pagerfile[0])
    mutt_unlink (pagerfile);

  return rc;
}