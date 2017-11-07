int mutt_save_message (HEADER *h, int delete, 
		       int decode, int decrypt, int *redraw)
{
  int i, need_buffy_cleanup;
  int need_passphrase = 0, app=0;
  char prompt[SHORT_STRING], buf[_POSIX_PATH_MAX];
  CONTEXT ctx;
  struct stat st;

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
    if (WithCrypto)
    {
      need_passphrase = h->security & ENCRYPT;
      app = h->security;
    }
    mutt_message_hook (Context, h, MUTT_MESSAGEHOOK);
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
      mutt_message_hook (Context, h, MUTT_MESSAGEHOOK);
      mutt_default_save (buf, sizeof (buf), h);
      if (WithCrypto)
      {
        need_passphrase = h->security & ENCRYPT;
        app = h->security;
      }
      h = NULL;
    }
  }

  mutt_pretty_mailbox (buf, sizeof (buf));
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
  if (mutt_save_confirm (buf, &st) != 0)
    return -1;

  if (WithCrypto && need_passphrase && (decode || decrypt)
      && !crypt_valid_passphrase(app))
    return -1;
  
  mutt_message (_("Copying to %s..."), buf);
  
#ifdef USE_IMAP
  if (Context->magic == MUTT_IMAP && 
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

  if (mx_open_mailbox (buf, MUTT_APPEND, &ctx) != NULL)
  {
    if (h)
    {
      if (_mutt_save_message(h, &ctx, delete, decode, decrypt) != 0)
      {
        mx_close_mailbox (&ctx, NULL);
        return -1;
      }
    }
    else
    {
      for (i = 0; i < Context->vcount; i++)
      {
	if (Context->hdrs[Context->v2r[i]]->tagged)
	{
	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], MUTT_MESSAGEHOOK);
	  if (_mutt_save_message(Context->hdrs[Context->v2r[i]],
			     &ctx, delete, decode, decrypt) != 0)
          {
            mx_close_mailbox (&ctx, NULL);
            return -1;
          }
	}
      }
    }

    need_buffy_cleanup = (ctx.magic == MUTT_MBOX || ctx.magic == MUTT_MMDF);

    mx_close_mailbox (&ctx, NULL);

    if (need_buffy_cleanup)
      mutt_buffy_cleanup (buf, &st);

    mutt_clear_error ();
    return (0);
  }
  
  return -1;
}