int mutt_compose_menu (HEADER *msg,   /* structure for new message */
                       char *fcc,     /* where to save a copy of the message */
                       size_t fcclen,
                       HEADER *cur,   /* current message */
                       int flags)
{
  char helpstr[LONG_STRING];
  char buf[LONG_STRING];
  char fname[_POSIX_PATH_MAX];
  MUTTMENU *menu;
  ATTACH_CONTEXT *actx;
  ATTACHPTR *new;
  int i, close = 0;
  int r = -1;		/* return value */
  int op = 0;
  int loop = 1;
  int fccSet = 0;	/* has the user edited the Fcc: field ? */
  CONTEXT *ctx = NULL, *this = NULL;
  /* Sort, SortAux could be changed in mutt_index_menu() */
  int oldSort, oldSortAux;
  struct stat st;
  compose_redraw_data_t rd;

  init_header_padding ();

  rd.msg = msg;
  rd.fcc = fcc;

  menu = mutt_new_menu (MENU_COMPOSE);
  menu->offset = HDR_ATTACH;
  menu->make_entry = snd_entry;
  menu->tag = mutt_tag_attach;
  menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_COMPOSE, ComposeHelp);
  menu->custom_menu_redraw = compose_menu_redraw;
  menu->redraw_data = &rd;
  mutt_push_current_menu (menu);

  actx = safe_calloc (sizeof(ATTACH_CONTEXT), 1);
  actx->hdr = msg;
  mutt_update_compose_menu (actx, menu, 1);

  while (loop)
  {
    switch (op = mutt_menuLoop (menu))
    {
      case OP_COMPOSE_EDIT_FROM:
	edit_address_list (HDR_FROM, &msg->env->from);
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
	break;
      case OP_COMPOSE_EDIT_TO:
	edit_address_list (HDR_TO, &msg->env->to);
	if (option (OPTCRYPTOPPORTUNISTICENCRYPT))
	{
	  crypt_opportunistic_encrypt (msg);
	  redraw_crypt_lines (msg);
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;
      case OP_COMPOSE_EDIT_BCC:
	edit_address_list (HDR_BCC, &msg->env->bcc);
	if (option (OPTCRYPTOPPORTUNISTICENCRYPT))
	{
	  crypt_opportunistic_encrypt (msg);
	  redraw_crypt_lines (msg);
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
	break;
      case OP_COMPOSE_EDIT_CC:
	edit_address_list (HDR_CC, &msg->env->cc);
	if (option (OPTCRYPTOPPORTUNISTICENCRYPT))
	{
	  crypt_opportunistic_encrypt (msg);
	  redraw_crypt_lines (msg);
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);	
        break;
      case OP_COMPOSE_EDIT_SUBJECT:
	if (msg->env->subject)
	  strfcpy (buf, msg->env->subject, sizeof (buf));
	else
	  buf[0] = 0;
	if (mutt_get_field (_("Subject: "), buf, sizeof (buf), 0) == 0)
	{
	  mutt_str_replace (&msg->env->subject, buf);
	  mutt_window_move (MuttIndexWindow, HDR_SUBJECT, HDR_XOFFSET);
	  if (msg->env->subject)
	    mutt_paddstr (W, msg->env->subject);
	  else
	    mutt_window_clrtoeol(MuttIndexWindow);
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;
      case OP_COMPOSE_EDIT_REPLY_TO:
	edit_address_list (HDR_REPLYTO, &msg->env->reply_to);
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
	break;
      case OP_COMPOSE_EDIT_FCC:
	strfcpy (buf, fcc, sizeof (buf));
	if (mutt_get_field (_("Fcc: "), buf, sizeof (buf), MUTT_FILE | MUTT_CLEAR) == 0)
	{
	  strfcpy (fcc, buf, fcclen);
	  mutt_pretty_mailbox (fcc, fcclen);
	  mutt_window_move (MuttIndexWindow, HDR_FCC, HDR_XOFFSET);
	  mutt_paddstr (W, fcc);
	  fccSet = 1;
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;
      case OP_COMPOSE_EDIT_MESSAGE:
	if (Editor && (mutt_strcmp ("builtin", Editor) != 0) && !option (OPTEDITHDRS))
	{
	  mutt_edit_file (Editor, msg->content->filename);
	  mutt_update_encoding (msg->content);
	  menu->redraw = REDRAW_FULL;
	  mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
	  break;
	}
	/* fall through */
      case OP_COMPOSE_EDIT_HEADERS:
	if (mutt_strcmp ("builtin", Editor) != 0 &&
	    (op == OP_COMPOSE_EDIT_HEADERS ||
	    (op == OP_COMPOSE_EDIT_MESSAGE && option (OPTEDITHDRS))))
	{
	  char *tag = NULL, *err = NULL;
	  mutt_env_to_local (msg->env);
	  mutt_edit_headers (NONULL (Editor), msg->content->filename, msg,
			     fcc, fcclen);
	  if (mutt_env_to_intl (msg->env, &tag, &err))
	  {
	    mutt_error (_("Bad IDN in \"%s\": '%s'"), tag, err);
	    FREE (&err);
	  }
	  if (option (OPTCRYPTOPPORTUNISTICENCRYPT))
	    crypt_opportunistic_encrypt (msg);
	}
	else
	{
	  /* this is grouped with OP_COMPOSE_EDIT_HEADERS because the
	     attachment list could change if the user invokes ~v to edit
	     the message with headers, in which we need to execute the
	     code below to regenerate the index array */
	  mutt_builtin_editor (msg->content->filename, msg, cur);
	}
	mutt_update_encoding (msg->content);

	/* attachments may have been added */
	if (actx->idxlen && actx->idx[actx->idxlen - 1]->content->next)
	{
          mutt_actx_free_entries (actx);
          mutt_update_compose_menu (actx, menu, 1);
	}

        menu->redraw = REDRAW_FULL;
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
	break;



      case OP_COMPOSE_ATTACH_KEY:
        if (!(WithCrypto & APPLICATION_PGP))
          break;

	new = (ATTACHPTR *) safe_calloc (1, sizeof (ATTACHPTR));
	if ((new->content = crypt_pgp_make_key_attachment(NULL)) != NULL)
	{
	  update_idx (menu, actx, new);
	  menu->redraw |= REDRAW_INDEX;
	}
	else
	  FREE (&new);

	menu->redraw |= REDRAW_STATUS;

        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;


      case OP_COMPOSE_ATTACH_FILE:
	{
	  char *prompt, **files;
	  int error, numfiles;

	  fname[0] = 0;
	  prompt = _("Attach file");
	  numfiles = 0;
	  files = NULL;

	  if (_mutt_enter_fname (prompt, fname, sizeof (fname), 0, 1, &files, &numfiles) == -1 ||
	      *fname == '\0')
	    break;

	  error = 0;
	  if (numfiles > 1)
	    mutt_message _("Attaching selected files...");
	  for (i = 0; i < numfiles; i++)
	  {
	    char *att = files[i];
	    new = (ATTACHPTR *) safe_calloc (1, sizeof (ATTACHPTR));
            new->unowned = 1;
	    new->content = mutt_make_file_attach (att);
	    if (new->content != NULL)
	      update_idx (menu, actx, new);
	    else
	    {
	      error = 1;
	      mutt_error (_("Unable to attach %s!"), att);
	      FREE (&new);
	    }
            FREE (&files[i]);
	  }

	  FREE (&files);
	  if (!error) mutt_clear_error ();

	  menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;

      case OP_COMPOSE_ATTACH_MESSAGE:
	{
	  char *prompt;
	  HEADER *h;

	  fname[0] = 0;
	  prompt = _("Open mailbox to attach message from");

	  if (Context)
	  {
	    strfcpy (fname, NONULL (Context->path), sizeof (fname));
	    mutt_pretty_mailbox (fname, sizeof (fname));
	  }

	  if (mutt_enter_fname (prompt, fname, sizeof (fname), 1) == -1 || !fname[0])
	    break;

	  mutt_expand_path (fname, sizeof (fname));
#ifdef USE_IMAP
          if (!mx_is_imap (fname))
#endif
#ifdef USE_POP
          if (!mx_is_pop (fname))
#endif
	  /* check to make sure the file exists and is readable */
	  if (access (fname, R_OK) == -1)
	  {
	    mutt_perror (fname);
	    break;
	  }

	  menu->redraw = REDRAW_FULL;

	  ctx = mx_open_mailbox (fname, MUTT_READONLY, NULL);
	  if (ctx == NULL)
	  {
	    mutt_error (_("Unable to open mailbox %s"), fname);
	    break;
	  }

	  if (!ctx->msgcount)
	  {
	    mx_close_mailbox (ctx, NULL);
	    FREE (&ctx);
	    mutt_error _("No messages in that folder.");
	    break;
	  }

	  this = Context; /* remember current folder and sort methods*/
	  oldSort = Sort; oldSortAux = SortAux;

	  Context = ctx;
	  set_option(OPTATTACHMSG);
	  mutt_message _("Tag the messages you want to attach!");
	  close = mutt_index_menu ();
	  unset_option(OPTATTACHMSG);

	  if (!Context)
	  {
	    /* go back to the folder we started from */
	    Context = this;
	    /* Restore old $sort and $sort_aux */
	    Sort = oldSort;
	    SortAux = oldSortAux;
	    menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	    break;
	  }

	  for (i = 0; i < Context->msgcount; i++)
	  {
	    h = Context->hdrs[i];
	    if (h->tagged)
	    {
	      new = (ATTACHPTR *) safe_calloc (1, sizeof (ATTACHPTR));
	      new->content = mutt_make_message_attach (Context, h, 1);
	      if (new->content != NULL)
		update_idx (menu, actx, new);
	      else
	      {
		mutt_error _("Unable to attach!");
		FREE (&new);
	      }
	    }
	  }
	  menu->redraw |= REDRAW_FULL;

	  if (close == OP_QUIT) 
	    mx_close_mailbox (Context, NULL);
	  else
	    mx_fastclose_mailbox (Context);
	  FREE (&Context);

	  /* go back to the folder we started from */
	  Context = this;
	  /* Restore old $sort and $sort_aux */
	  Sort = oldSort;
	  SortAux = oldSortAux;
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;

      case OP_DELETE:
	CHECK_COUNT;
        if (CURATTACH->unowned)
          CURATTACH->content->unlink = 0;
	if (delete_attachment (actx, menu->current) == -1)
	  break;
	mutt_update_compose_menu (actx, menu, 0);
	if (menu->current == 0)
	  msg->content = actx->idx[0]->content;

        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;

      case OP_COMPOSE_TOGGLE_RECODE:
      {
        CHECK_COUNT;
        if (!mutt_is_text_part (CURATTACH->content))
        {
	  mutt_error (_("Recoding only affects text attachments."));
	  break;
	}
        CURATTACH->content->noconv = !CURATTACH->content->noconv;
        if (CURATTACH->content->noconv)
	  mutt_message (_("The current attachment won't be converted."));
        else
	  mutt_message (_("The current attachment will be converted."));
	menu->redraw = REDRAW_CURRENT;
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;
      }

      case OP_COMPOSE_EDIT_DESCRIPTION:
	CHECK_COUNT;
	strfcpy (buf,
		 CURATTACH->content->description ?
		 CURATTACH->content->description : "",
		 sizeof (buf));
	/* header names should not be translated */
	if (mutt_get_field ("Description: ", buf, sizeof (buf), 0) == 0)
	{
	  mutt_str_replace (&CURATTACH->content->description, buf);
	  menu->redraw = REDRAW_CURRENT;
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;

      case OP_COMPOSE_UPDATE_ENCODING:
        CHECK_COUNT;
        if (menu->tagprefix)
        {
	  BODY *top;
	  for (top = msg->content; top; top = top->next)
	  {
	    if (top->tagged)
	      mutt_update_encoding (top);
	  }
	  menu->redraw = REDRAW_FULL;
	}
        else
        {
          mutt_update_encoding(CURATTACH->content);
	  menu->redraw = REDRAW_CURRENT | REDRAW_STATUS;
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;
      
      case OP_COMPOSE_TOGGLE_DISPOSITION:
	/* toggle the content-disposition between inline/attachment */
	CURATTACH->content->disposition = (CURATTACH->content->disposition == DISPINLINE) ? DISPATTACH : DISPINLINE;
	menu->redraw = REDRAW_CURRENT;
	break;

      case OP_EDIT_TYPE:
	CHECK_COUNT;
        {
	  mutt_edit_content_type (NULL, CURATTACH->content, NULL);

	  /* this may have been a change to text/something */
	  mutt_update_encoding (CURATTACH->content);

	  menu->redraw = REDRAW_CURRENT;
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;

      case OP_COMPOSE_EDIT_ENCODING:
	CHECK_COUNT;
	strfcpy (buf, ENCODING (CURATTACH->content->encoding),
							      sizeof (buf));
	if (mutt_get_field ("Content-Transfer-Encoding: ", buf,
					    sizeof (buf), 0) == 0 && buf[0])
	{
	  if ((i = mutt_check_encoding (buf)) != ENCOTHER && i != ENCUUENCODED)
	  {
	    CURATTACH->content->encoding = i;
	    menu->redraw = REDRAW_CURRENT | REDRAW_STATUS;
	    mutt_clear_error();
	  }
	  else
	    mutt_error _("Invalid encoding.");
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;

      case OP_COMPOSE_SEND_MESSAGE:

        /* Note: We don't invoke send2-hook here, since we want to leave
	 * users an opportunity to change settings from the ":" prompt.
	 */
      
        if(check_attachments(actx) != 0)
        {
	  menu->redraw = REDRAW_FULL;
	  break;
	}

      
#ifdef MIXMASTER
        if (msg->chain && mix_check_message (msg) != 0)
	  break;
#endif
      
	if (!fccSet && *fcc)
	{
	  if ((i = query_quadoption (OPT_COPY,
				_("Save a copy of this message?"))) == -1)
	    break;
	  else if (i == MUTT_NO)
	    *fcc = 0;
	}

	loop = 0;
	r = 0;
	break;

      case OP_COMPOSE_EDIT_FILE:
	CHECK_COUNT;
	mutt_edit_file (NONULL(Editor), CURATTACH->content->filename);
	mutt_update_encoding (CURATTACH->content);
	menu->redraw = REDRAW_CURRENT | REDRAW_STATUS;
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
	break;

      case OP_COMPOSE_TOGGLE_UNLINK:
	CHECK_COUNT;
	CURATTACH->content->unlink = !CURATTACH->content->unlink;

#if 0
        /* OPTRESOLVE is otherwise ignored on this menu.
	 * Where's the bug?
	 */

        if (option (OPTRESOLVE) && menu->current + 1 < menu->max)
	  menu->current++;
# endif
	menu->redraw = REDRAW_INDEX;
        /* No send2hook since this doesn't change the message. */
	break;

      case OP_COMPOSE_GET_ATTACHMENT:
        CHECK_COUNT;
        if(menu->tagprefix)
        {
	  BODY *top;
	  for(top = msg->content; top; top = top->next)
	  {
	    if(top->tagged)
	      mutt_get_tmp_attachment(top);
	  }
	  menu->redraw = REDRAW_FULL;
	}
        else if (mutt_get_tmp_attachment(CURATTACH->content) == 0)
	  menu->redraw = REDRAW_CURRENT;

        /* No send2hook since this doesn't change the message. */
        break;

      case OP_COMPOSE_RENAME_ATTACHMENT:
        {
          char *src;
          int ret;

          CHECK_COUNT;
          if (CURATTACH->content->d_filename)
            src = CURATTACH->content->d_filename;
          else
            src = CURATTACH->content->filename;
          strfcpy (fname, mutt_basename (NONULL (src)), sizeof (fname));
          ret = mutt_get_field (_("Send attachment with name: "),
                                fname, sizeof (fname), MUTT_FILE);
          if (ret == 0)
          {
            /*
             * As opposed to RENAME_FILE, we don't check fname[0] because it's
             * valid to set an empty string here, to erase what was set
             */
            mutt_str_replace (&CURATTACH->content->d_filename, fname);
            menu->redraw = REDRAW_CURRENT;
          }
        }
        break;

      case OP_COMPOSE_RENAME_FILE:
	CHECK_COUNT;
	strfcpy (fname, CURATTACH->content->filename, sizeof (fname));
	mutt_pretty_mailbox (fname, sizeof (fname));
	if (mutt_get_field (_("Rename to: "), fname, sizeof (fname), MUTT_FILE)
							== 0 && fname[0])
	{
	  if (stat(CURATTACH->content->filename, &st) == -1)
	  {
            /* L10N:
               "stat" is a system call. Do "man 2 stat" for more information. */
	    mutt_error (_("Can't stat %s: %s"), fname, strerror (errno));
	    break;
	  }

	  mutt_expand_path (fname, sizeof (fname));
	  if(mutt_rename_file (CURATTACH->content->filename, fname))
	    break;
	  
	  mutt_str_replace (&CURATTACH->content->filename, fname);
	  menu->redraw = REDRAW_CURRENT;

	  if(CURATTACH->content->stamp >= st.st_mtime)
	    mutt_stamp_attachment(CURATTACH->content);
	  
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;

      case OP_COMPOSE_NEW_MIME:
	{
	  char type[STRING];
	  char *p;
	  int itype;
	  FILE *fp;

          mutt_window_clearline (MuttMessageWindow, 0);
	  fname[0] = 0;
	  if (mutt_get_field (_("New file: "), fname, sizeof (fname), MUTT_FILE)
	      != 0 || !fname[0])
	    continue;
	  mutt_expand_path (fname, sizeof (fname));

	  /* Call to lookup_mime_type () ?  maybe later */
	  type[0] = 0;
	  if (mutt_get_field ("Content-Type: ", type, sizeof (type), 0) != 0 
	      || !type[0])
	    continue;

	  if (!(p = strchr (type, '/')))
	  {
	    mutt_error _("Content-Type is of the form base/sub");
	    continue;
	  }
	  *p++ = 0;
	  if ((itype = mutt_check_mime_type (type)) == TYPEOTHER)
	  {
	    mutt_error (_("Unknown Content-Type %s"), type);
	    continue;
	  }

	  new = (ATTACHPTR *) safe_calloc (1, sizeof (ATTACHPTR));
	  /* Touch the file */
	  if (!(fp = safe_fopen (fname, "w")))
	  {
	    mutt_error (_("Can't create file %s"), fname);
	    FREE (&new);
	    continue;
	  }
	  safe_fclose (&fp);

	  if ((new->content = mutt_make_file_attach (fname)) == NULL)
	  {
	    mutt_error _("What we have here is a failure to make an attachment");
            FREE (&new);
	    continue;
	  }
	  update_idx (menu, actx, new);

	  CURATTACH->content->type = itype;
	  mutt_str_replace (&CURATTACH->content->subtype, p);
	  CURATTACH->content->unlink = 1;
	  menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;

	  if (mutt_compose_attachment (CURATTACH->content))
	  {
	    mutt_update_encoding (CURATTACH->content);
	    menu->redraw = REDRAW_FULL;
	  }
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);    
        break;

      case OP_COMPOSE_EDIT_MIME:
	CHECK_COUNT;
	if (mutt_edit_attachment (CURATTACH->content))
	{
	  mutt_update_encoding (CURATTACH->content);
	  menu->redraw = REDRAW_FULL;
	}
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;

      case OP_VIEW_ATTACH:
      case OP_DISPLAY_HEADERS:
	CHECK_COUNT;
	mutt_attach_display_loop (menu, op, NULL, actx, 0);
	menu->redraw = REDRAW_FULL;
        /* no send2hook, since this doesn't modify the message */
	break;

      case OP_SAVE:
	CHECK_COUNT;
	mutt_save_attachment_list (actx, NULL, menu->tagprefix, CURATTACH->content, NULL, menu);
        /* no send2hook, since this doesn't modify the message */
	break;

      case OP_PRINT:
	CHECK_COUNT;
	mutt_print_attachment_list (actx, NULL, menu->tagprefix, CURATTACH->content);
        /* no send2hook, since this doesn't modify the message */
	break;

      case OP_PIPE:
      case OP_FILTER:
        CHECK_COUNT;
	mutt_pipe_attachment_list (actx, NULL, menu->tagprefix, CURATTACH->content, op == OP_FILTER);
	if (op == OP_FILTER) /* cte might have changed */
	  menu->redraw = menu->tagprefix ? REDRAW_FULL : REDRAW_CURRENT;
        menu->redraw |= REDRAW_STATUS;
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
	break;

      case OP_EXIT:
	if ((i = query_quadoption (OPT_POSTPONE, _("Postpone this message?"))) == MUTT_NO)
	{
          for (i = 0; i < actx->idxlen; i++)
            if (actx->idx[i]->unowned)
              actx->idx[i]->content->unlink = 0;

          if (!(flags & MUTT_COMPOSE_NOFREEHEADER))
          {
            for (i = 0; i < actx->idxlen; i++)
            {
              /* avoid freeing other attachments */
              actx->idx[i]->content->next = NULL;
              actx->idx[i]->content->parts = NULL;
              mutt_free_body (&actx->idx[i]->content);
            }
          }
	  r = -1;
	  loop = 0;
	  break;
	}
	else if (i == -1)
	  break; /* abort */

	/* fall through to postpone! */

      case OP_COMPOSE_POSTPONE_MESSAGE:

        if(check_attachments(actx) != 0)
        {
	  menu->redraw = REDRAW_FULL;
	  break;
	}
      
	loop = 0;
	r = 1;
	break;

      case OP_COMPOSE_ISPELL:
	endwin ();
	snprintf (buf, sizeof (buf), "%s -x %s", NONULL(Ispell), msg->content->filename);
	if (mutt_system (buf) == -1)
	  mutt_error (_("Error running \"%s\"!"), buf);
	else
        {
	  mutt_update_encoding (msg->content);
	  menu->redraw |= REDRAW_STATUS;
	}
	break;

      case OP_COMPOSE_WRITE_MESSAGE:

       fname[0] = '\0';
       if (Context)
       {
	 strfcpy (fname, NONULL (Context->path), sizeof (fname));
	 mutt_pretty_mailbox (fname, sizeof (fname));
       }
       if (actx->idxlen)
         msg->content = actx->idx[0]->content;
       if (mutt_enter_fname (_("Write message to mailbox"), fname, sizeof (fname),
                             1) != -1 && fname[0])
       {
         mutt_message (_("Writing message to %s ..."), fname);
         mutt_expand_path (fname, sizeof (fname));

         if (msg->content->next)
           msg->content = mutt_make_multipart (msg->content);

         if (mutt_write_fcc (fname, msg, NULL, 0, NULL) < 0)
           msg->content = mutt_remove_multipart (msg->content);
         else
           mutt_message _("Message written.");
       }
       break;



      case OP_COMPOSE_PGP_MENU:
        if (!(WithCrypto & APPLICATION_PGP))
          break;
	if ((WithCrypto & APPLICATION_SMIME)
            && (msg->security & APPLICATION_SMIME))
	{
          if (msg->security & (ENCRYPT | SIGN))
          {
            if (mutt_yesorno (_("S/MIME already selected. Clear & continue ? "),
                              MUTT_YES) != MUTT_YES)
            {
              mutt_clear_error ();
              break;
            }
            msg->security &= ~(ENCRYPT | SIGN);
          }
	  msg->security &= ~APPLICATION_SMIME;
	  msg->security |= APPLICATION_PGP;
          crypt_opportunistic_encrypt (msg);
          redraw_crypt_lines (msg);
	}
	msg->security = crypt_pgp_send_menu (msg);
	redraw_crypt_lines (msg);
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;


      case OP_FORGET_PASSPHRASE:
	crypt_forget_passphrase ();
	break;


      case OP_COMPOSE_SMIME_MENU:
        if (!(WithCrypto & APPLICATION_SMIME))
          break;

	if ((WithCrypto & APPLICATION_PGP)
            && (msg->security & APPLICATION_PGP))
	{
          if (msg->security & (ENCRYPT | SIGN))
          {
            if (mutt_yesorno (_("PGP already selected. Clear & continue ? "),
                                MUTT_YES) != MUTT_YES)
            {
              mutt_clear_error ();
              break;
            }
            msg->security &= ~(ENCRYPT | SIGN);
          }
	  msg->security &= ~APPLICATION_PGP;
	  msg->security |= APPLICATION_SMIME;
          crypt_opportunistic_encrypt (msg);
          redraw_crypt_lines (msg);
	}
	msg->security = crypt_smime_send_menu(msg);
	redraw_crypt_lines (msg);
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;


#ifdef MIXMASTER
      case OP_COMPOSE_MIX:
      
      	mix_make_chain (&msg->chain);
        mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
        break;
#endif

    }
  }

  mutt_pop_current_menu (menu);
  mutt_menuDestroy (&menu);

  if (actx->idxlen)
    msg->content = actx->idx[0]->content;
  else
    msg->content = NULL;

  mutt_free_attach_context (&actx);

  return (r);
}