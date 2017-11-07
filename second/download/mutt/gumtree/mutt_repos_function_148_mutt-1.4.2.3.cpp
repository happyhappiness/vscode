int mutt_save_message (HEADER *h, int delete, 
		       int decode, int decrypt, int *redraw)
{
  int i, need_buffy_cleanup;
#ifdef HAVE_PGP
  int need_passphrase = 0;
#endif
  char prompt[SHORT_STRING], buf[_POSIX_PATH_MAX];
  CONTEXT ctx;
  struct stat st;
#ifdef BUFFY_SIZE
  BUFFY *tmp = NULL;
#else
  struct utimbuf ut;
#endif

  *redraw = 0;

  
  snprintf (prompt, sizeof (prompt),
	    decode  ? (delete ? _("Decode-save%s to mailbox") :
		       _("Decode-copy%s to mailbox")) :
	    (decrypt ? (delete ? _("Decrypt-save%s to mailbox") :
			_("Decrypt-copy%s to mailbox")) :
	     (delete ? _("Save%s to mailbox") : _("Copy%s to mailbox"))),
	    h ? "" : _(" tagged"));
  
  if (h)
  {
#ifdef HAVE_PGP
    need_passphrase = h->pgp & PGPENCRYPT;
#endif
    mutt_message_hook (Context, h, M_MESSAGEHOOK);
    mutt_default_save (buf, sizeof (buf), h);
  }
  else
  {
    /* look for the first tagged message */

    for (i = 0; i < Context->vcount; i++)
    {
      if (Context->hdrs[Context->v2r[i]]->tagged)
      {
	h = Context->hdrs[Context->v2r[i]];
	break;
      }
    }

    if (h)
    {
      mutt_message_hook (Context, h, M_MESSAGEHOOK);
      mutt_default_save (buf, sizeof (buf), h);
#ifdef HAVE_PGP
      need_passphrase |= h->pgp & PGPENCRYPT;
#endif
      h = NULL;
    }
  }

  mutt_pretty_mailbox (buf);
  if (mutt_enter_fname (prompt, buf, sizeof (buf), redraw, 0) == -1)
    return (-1);

  if (*redraw != REDRAW_FULL)
  {
    if (!h)
      *redraw = REDRAW_INDEX | REDRAW_STATUS;
    else
      *redraw = REDRAW_STATUS;
  }

  if (!buf[0])
    return (-1);
 
  /* This is an undocumented feature of ELM pointed out to me by Felix von
   * Leitner <leitner@prz.fu-berlin.de>
   */
  if (mutt_strcmp (buf, ".") == 0)
    strfcpy (buf, LastSaveFolder, sizeof (buf));
  else
    strfcpy (LastSaveFolder, buf, sizeof (LastSaveFolder));

  mutt_expand_path (buf, sizeof (buf));

  /* check to make sure that this file is really the one the user wants */
  if (!mutt_save_confirm (buf, &st))
    return -1;

#ifdef HAVE_PGP
  if(need_passphrase && (decode || decrypt) && !pgp_valid_passphrase())
    return -1;
#endif
  
  mutt_message (_("Copying to %s..."), buf);
  
#ifdef USE_IMAP
  if (Context->magic == M_IMAP && 
      !(decode || decrypt) && mx_is_imap (buf))
  {
    switch (imap_copy_messages (Context, h, buf, delete))
    {
      /* success */
      case 0: mutt_clear_error (); return 0;
      /* non-fatal error: fall through to fetch/append */
      case 1: break;
      /* fatal error, abort */
      case -1: return -1;
    }
  }
#endif

  if (mx_open_mailbox (buf, M_APPEND, &ctx) != NULL)
  {
    if (h)
      _mutt_save_message(h, &ctx, delete, decode, decrypt);
    else
    {
      for (i = 0; i < Context->vcount; i++)
      {
	if (Context->hdrs[Context->v2r[i]]->tagged)
	{
	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], M_MESSAGEHOOK);
	  _mutt_save_message(Context->hdrs[Context->v2r[i]],
			     &ctx, delete, decode, decrypt);
	}
      }
    }

    need_buffy_cleanup = (ctx.magic == M_MBOX || ctx.magic == M_MMDF || ctx.magic == M_KENDRA);

    mx_close_mailbox (&ctx, NULL);

    if (need_buffy_cleanup)
    {
#ifdef BUFFY_SIZE
      tmp = mutt_find_mailbox (buf);
      if (tmp && !tmp->new)
	mutt_update_mailbox (tmp);
#else
      /* fix up the times so buffy won't get confused */
      if (st.st_mtime > st.st_atime)
      {
	ut.actime = st.st_atime;
	ut.modtime = time (NULL);
	utime (buf, &ut); 
      }
      else
	utime (buf, NULL);
#endif
    }

    mutt_clear_error ();
    return (0);
  }
  
  return -1;
}