int mutt_display_message (HEADER *cur)
{
  char tempfile[_POSIX_PATH_MAX], buf[LONG_STRING];
  int rc = 0, builtin = 0;
  int cmflags = M_CM_DECODE | M_CM_DISPLAY | M_CM_CHARCONV;
  FILE *fpout = NULL;
  FILE *fpfilterout = NULL;
  pid_t filterpid = -1;
  int res;

  snprintf (buf, sizeof (buf), "%s/%s", TYPE (cur->content),
	    cur->content->subtype);

  mutt_parse_mime_message (Context, cur);
  mutt_message_hook (Context, cur, M_MESSAGEHOOK);

#ifdef HAVE_PGP
  /* see if PGP is needed for this message.  if so, we should exit curses */
  if (cur->pgp)
  {
    if (cur->pgp & PGPENCRYPT)
    {
      if (!pgp_valid_passphrase ())
	return 0;

      cmflags |= M_CM_VERIFY;
    }
    else if (cur->pgp & PGPSIGN)
    {
      /* find out whether or not the verify signature */
      if (query_quadoption (OPT_VERIFYSIG, _("Verify PGP signature?")) == M_YES)
      {
	cmflags |= M_CM_VERIFY;
      }
    }
  }
  
  if ((cmflags & M_CM_VERIFY) || (cur->pgp & PGPENCRYPT))
  {
    if (cur->env->from)
      pgp_invoke_getkeys (cur->env->from);

    mutt_message _("Invoking PGP...");
  }

#endif

  mutt_mktemp (tempfile);
  if ((fpout = safe_fopen (tempfile, "w")) == NULL)
  {
    mutt_error _("Could not create temporary file!");
    return (0);
  }

  if (DisplayFilter && *DisplayFilter) 
  {
    fpfilterout = fpout;
    fpout = NULL;
    /* mutt_endwin (NULL); */
    filterpid = mutt_create_filter_fd (DisplayFilter, &fpout, NULL, NULL,
				       -1, fileno(fpfilterout), -1);
    if (filterpid < 0)
    {
      mutt_error (_("Cannot create display filter"));
      safe_fclose (&fpfilterout);
      unlink (tempfile);
      return 0;
    }
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
    }
    mutt_unlink (tempfile);
    return 0;
  }

  if (fpfilterout != NULL && mutt_wait_filter (filterpid) != 0)
    mutt_any_key_to_continue (NULL);

  safe_fclose (&fpfilterout);
  
#ifdef HAVE_PGP
  /* update PGP information for this message */
  cur->pgp |= pgp_query (cur->content);
#endif

  if (builtin)
  {
    pager_t info;

#ifdef HAVE_PGP
    if (cmflags & M_CM_VERIFY)
      mutt_message ((cur->pgp & PGPGOODSIGN) ?
		    _("PGP signature successfully verified.") :
		    _("PGP signature could NOT be verified."));
#endif

    /* Invoke the builtin pager */
    memset (&info, 0, sizeof (pager_t));
    info.hdr = cur;
    info.ctx = Context;
    rc = mutt_pager (NULL, tempfile, M_PAGER_MESSAGE, &info);
  }
  else
  {
    int r;

    mutt_endwin (NULL);
    snprintf (buf, sizeof (buf), "%s %s", NONULL(Pager), tempfile);
    if ((r = mutt_system (buf)) == -1)
      mutt_error (_("Error running \"%s\"!"), buf);
    unlink (tempfile);
    keypad (stdscr, TRUE);
    if (r != -1)
      mutt_set_flag (Context, cur, M_READ, 1);
    if (r != -1 && option (OPTPROMPTAFTER))
    {
      mutt_ungetch (mutt_any_key_to_continue _("Command: "), 0);
      rc = km_dokey (MENU_PAGER);
    }
    else
      rc = 0;
  }

  return rc;
}