int
ci_send_message (int flags,		/* send mode */
		 HEADER *msg,		/* template to use for new message */
		 char *tempfile,	/* file specified by -i or -H */
		 CONTEXT *ctx,		/* current mailbox */
		 HEADER *cur)		/* current message */
{
  char buffer[LONG_STRING];
  char fcc[_POSIX_PATH_MAX] = ""; /* where to copy this message */
  FILE *tempfp = NULL;
  BODY *pbody;
  int i, killfrom = 0;
  int fcc_error = 0;
  int free_clear_content = 0;

  BODY *save_content = NULL;
  BODY *clear_content = NULL;
  char *pgpkeylist = NULL;
  /* save current value of "pgp_sign_as"  and "smime_default_key" */
  char *pgp_signas = NULL;
  char *smime_default_key = NULL;
  char *tag = NULL, *err = NULL;
  char *ctype;

  int rv = -1;
  
  if (!flags && !msg && quadoption (OPT_RECALL) != MUTT_NO &&
      mutt_num_postponed (1))
  {
    /* If the user is composing a new message, check to see if there
     * are any postponed messages first.
     */
    if ((i = query_quadoption (OPT_RECALL, _("Recall postponed message?"))) == -1)
      return rv;

    if(i == MUTT_YES)
      flags |= SENDPOSTPONED;
  }
  
  
  if (flags & SENDPOSTPONED)
  {
    if (WithCrypto & APPLICATION_PGP)
      pgp_signas = safe_strdup(PgpSignAs);
    if (WithCrypto & APPLICATION_SMIME)
      smime_default_key = safe_strdup(SmimeDefaultKey);
  }

  /* Delay expansion of aliases until absolutely necessary--shouldn't
   * be necessary unless we are prompting the user or about to execute a
   * send-hook.
   */

  if (!msg)
  {
    msg = mutt_new_header ();

    if (flags == SENDPOSTPONED)
    {
      if ((flags = mutt_get_postponed (ctx, msg, &cur, fcc, sizeof (fcc))) < 0)
	goto cleanup;
    }

    if (flags & (SENDPOSTPONED|SENDRESEND))
    {
      if ((tempfp = safe_fopen (msg->content->filename, "a+")) == NULL)
      {
	mutt_perror (msg->content->filename);
	goto cleanup;
      }
    }

    if (!msg->env)
      msg->env = mutt_new_envelope ();
  }

  /* Parse and use an eventual list-post header */
  if ((flags & SENDLISTREPLY) 
      && cur && cur->env && cur->env->list_post) 
  {
    /* Use any list-post header as a template */
    url_parse_mailto (msg->env, NULL, cur->env->list_post);
    /* We don't let them set the sender's address. */
    rfc822_free_address (&msg->env->from);
  }
  
  if (! (flags & (SENDKEY | SENDPOSTPONED | SENDRESEND)))
  {
    /* When SENDDRAFTFILE is set, the caller has already
     * created the "parent" body structure.
     */
    if (! (flags & SENDDRAFTFILE))
    {
      pbody = mutt_new_body ();
      pbody->next = msg->content; /* don't kill command-line attachments */
      msg->content = pbody;

      if (!(ctype = safe_strdup (ContentType)))
        ctype = safe_strdup ("text/plain");
      mutt_parse_content_type (ctype, msg->content);
      FREE (&ctype);
      msg->content->unlink = 1;
      msg->content->use_disp = 0;
      msg->content->disposition = DISPINLINE;

      if (!tempfile)
      {
        mutt_mktemp (buffer, sizeof (buffer));
        tempfp = safe_fopen (buffer, "w+");
        msg->content->filename = safe_strdup (buffer);
      }
      else
      {
        tempfp = safe_fopen (tempfile, "a+");
        msg->content->filename = safe_strdup (tempfile);
      }
    }
    else
      tempfp = safe_fopen (msg->content->filename, "a+");

    if (!tempfp)
    {
      dprint(1,(debugfile, "newsend_message: can't create tempfile %s (errno=%d)\n", msg->content->filename, errno));
      mutt_perror (msg->content->filename);
      goto cleanup;
    }
  }

  /* this is handled here so that the user can match ~f in send-hook */
  if (cur && option (OPTREVNAME) && !(flags & (SENDPOSTPONED|SENDRESEND)))
  {
    /* we shouldn't have to worry about freeing `msg->env->from' before
     * setting it here since this code will only execute when doing some
     * sort of reply.  the pointer will only be set when using the -H command
     * line option.
     *
     * We shouldn't have to worry about alias expansion here since we are
     * either replying to a real or postponed message, therefore no aliases
     * should exist since the user has not had the opportunity to add
     * addresses to the list.  We just have to ensure the postponed messages
     * have their aliases expanded.
     */

    msg->env->from = set_reverse_name (cur->env);
  }

  if (! (flags & (SENDPOSTPONED|SENDRESEND)) &&
      ! ((flags & SENDDRAFTFILE) && option (OPTRESUMEDRAFTFILES)))
  {
    if ((flags & (SENDREPLY | SENDFORWARD)) && ctx &&
	envelope_defaults (msg->env, ctx, cur, flags) == -1)
      goto cleanup;

    if (option (OPTHDRS))
      process_user_recips (msg->env);

    /* Expand aliases and remove duplicates/crossrefs */
    mutt_expand_aliases_env (msg->env);
    
    if (flags & SENDREPLY)
      mutt_fix_reply_recipients (msg->env);

    if (! (flags & (SENDMAILX|SENDBATCH)) &&
	! (option (OPTAUTOEDIT) && option (OPTEDITHDRS)) &&
	! ((flags & SENDREPLY) && option (OPTFASTREPLY)))
    {
      if (edit_envelope (msg->env) == -1)
	goto cleanup;
    }

    /* the from address must be set here regardless of whether or not
     * $use_from is set so that the `~P' (from you) operator in send-hook
     * patterns will work.  if $use_from is unset, the from address is killed
     * after send-hooks are evaluated */

    if (!msg->env->from)
    {
      msg->env->from = mutt_default_from ();
      killfrom = 1;
    }

    if ((flags & SENDREPLY) && cur)
    {
      /* change setting based upon message we are replying to */
      mutt_message_hook (ctx, cur, MUTT_REPLYHOOK);

      /*
       * set the replied flag for the message we are generating so that the
       * user can use ~Q in a send-hook to know when reply-hook's are also
       * being used.
       */
      msg->replied = 1;
    }

    /* change settings based upon recipients */
    
    mutt_message_hook (NULL, msg, MUTT_SENDHOOK);

    /*
     * Unset the replied flag from the message we are composing since it is
     * no longer required.  This is done here because the FCC'd copy of
     * this message was erroneously get the 'R'eplied flag when stored in
     * a maildir-style mailbox.
     */
    msg->replied = 0;

    if (! (flags & SENDKEY))
    {
      if (option (OPTTEXTFLOWED) && msg->content->type == TYPETEXT && !ascii_strcasecmp (msg->content->subtype, "plain"))
        mutt_set_parameter ("format", "flowed", &msg->content->parameter);
    }

    /* $use_from and/or $from might have changed in a send-hook */
    if (killfrom)
    {
      rfc822_free_address (&msg->env->from);
      if (option (OPTUSEFROM) && !(flags & (SENDPOSTPONED|SENDRESEND)))
	msg->env->from = mutt_default_from ();
      killfrom = 0;
    }

    if (option (OPTHDRS))
      process_user_header (msg->env);

    if (flags & SENDBATCH)
       mutt_copy_stream (stdin, tempfp);

    if (option (OPTSIGONTOP) && ! (flags & (SENDMAILX|SENDKEY|SENDBATCH))
	&& Editor && mutt_strcmp (Editor, "builtin") != 0)
      append_signature (tempfp);

    /* include replies/forwarded messages, unless we are given a template */
    if (!tempfile && (ctx || !(flags & (SENDREPLY|SENDFORWARD)))
	&& generate_body (tempfp, msg, flags, ctx, cur) == -1)
      goto cleanup;

    if (!option (OPTSIGONTOP) && ! (flags & (SENDMAILX|SENDKEY|SENDBATCH))
	&& Editor && mutt_strcmp (Editor, "builtin") != 0)
      append_signature (tempfp);
  }
  
  /* 
   * This hook is even called for postponed messages, and can, e.g., be
   * used for setting the editor, the sendmail path, or the
   * envelope sender.
   */
  mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);

  /* wait until now to set the real name portion of our return address so
     that $realname can be set in a send-hook */
  if (msg->env->from && !msg->env->from->personal
      && !(flags & (SENDRESEND|SENDPOSTPONED)))
    msg->env->from->personal = safe_strdup (Realname);

  if (!((WithCrypto & APPLICATION_PGP) && (flags & SENDKEY)))
    safe_fclose (&tempfp);

  if (flags & SENDMAILX)
  {
    if (mutt_builtin_editor (msg->content->filename, msg, cur) == -1)
      goto cleanup;
  }
  else if (! (flags & SENDBATCH))
  {
    struct stat st;
    time_t mtime = mutt_decrease_mtime (msg->content->filename, NULL);

    mutt_update_encoding (msg->content);

    /*
     * Select whether or not the user's editor should be called now.  We
     * don't want to do this when:
     * 1) we are sending a key/cert
     * 2) we are forwarding a message and the user doesn't want to edit it.
     *    This is controlled by the quadoption $forward_edit.  However, if
     *    both $edit_headers and $autoedit are set, we want to ignore the
     *    setting of $forward_edit because the user probably needs to add the
     *    recipients.
     */
    if (! (flags & SENDKEY) &&
	((flags & SENDFORWARD) == 0 ||
	 (option (OPTEDITHDRS) && option (OPTAUTOEDIT)) ||
	 query_quadoption (OPT_FORWEDIT, _("Edit forwarded message?")) == MUTT_YES))
    {
      /* If the this isn't a text message, look for a mailcap edit command */
      if (mutt_needs_mailcap (msg->content))
      {
	if (!mutt_edit_attachment (msg->content))
          goto cleanup;
      }
      else if (!Editor || mutt_strcmp ("builtin", Editor) == 0)
	mutt_builtin_editor (msg->content->filename, msg, cur);
      else if (option (OPTEDITHDRS))
      {
	mutt_env_to_local (msg->env);
	mutt_edit_headers (Editor, msg->content->filename, msg, fcc, sizeof (fcc));
	mutt_env_to_intl (msg->env, NULL, NULL);
      }
      else
      {
	mutt_edit_file (Editor, msg->content->filename);
	if (stat (msg->content->filename, &st) == 0)
	{
	  if (mtime != st.st_mtime)
	    fix_end_of_file (msg->content->filename);
	}
	else
	  mutt_perror (msg->content->filename);
      }
      
      /* If using format=flowed, perform space stuffing.  Avoid stuffing when
       * recalling a postponed message where the stuffing was already
       * performed.  If it has already been performed, the format=flowed
       * parameter will be present.
       */
      if (option (OPTTEXTFLOWED) && msg->content->type == TYPETEXT && !ascii_strcasecmp("plain", msg->content->subtype))
      {
	char *p = mutt_get_parameter("format", msg->content->parameter);
	if (ascii_strcasecmp("flowed", NONULL(p)))
	  rfc3676_space_stuff (msg);
      }

      mutt_message_hook (NULL, msg, MUTT_SEND2HOOK);
    }

    if (! (flags & (SENDPOSTPONED | SENDFORWARD | SENDKEY | SENDRESEND | SENDDRAFTFILE)))
    {
      if (stat (msg->content->filename, &st) == 0)
      {
	/* if the file was not modified, bail out now */
	if (mtime == st.st_mtime && !msg->content->next &&
	    query_quadoption (OPT_ABORT, _("Abort unmodified message?")) == MUTT_YES)
	{
	  mutt_message _("Aborted unmodified message.");
	  goto cleanup;
	}
      }
      else
	mutt_perror (msg->content->filename);
    }
  }

  /* 
   * Set the message security unless:
   * 1) crypto support is not enabled (WithCrypto==0)
   * 2) pgp: header field was present during message editing with $edit_headers (msg->security != 0)
   * 3) we are resending a message
   * 4) we are recalling a postponed message (don't override the user's saved settings)
   * 5) we are in mailx mode
   * 6) we are in batch mode
   *
   * This is done after allowing the user to edit the message so that security
   * settings can be configured with send2-hook and $edit_headers.
   */
  if (WithCrypto && (msg->security == 0) && !(flags & (SENDBATCH | SENDMAILX | SENDPOSTPONED | SENDRESEND)))
  {
    if (option (OPTCRYPTAUTOSIGN))
      msg->security |= SIGN;
    if (option (OPTCRYPTAUTOENCRYPT))
      msg->security |= ENCRYPT;
    if (option (OPTCRYPTREPLYENCRYPT) && cur && (cur->security & ENCRYPT))
      msg->security |= ENCRYPT;
    if (option (OPTCRYPTREPLYSIGN) && cur && (cur->security & SIGN))
      msg->security |= SIGN;
    if (option (OPTCRYPTREPLYSIGNENCRYPTED) && cur && (cur->security & ENCRYPT))
      msg->security |= SIGN;
    if ((WithCrypto & APPLICATION_PGP) &&
        ((msg->security & (ENCRYPT | SIGN)) || option (OPTCRYPTOPPORTUNISTICENCRYPT)))
    {
      if (option (OPTPGPAUTOINLINE))
	msg->security |= INLINE;
      if (option (OPTPGPREPLYINLINE) && cur && (cur->security & INLINE))
	msg->security |= INLINE;
    }

    if (msg->security || option (OPTCRYPTOPPORTUNISTICENCRYPT))
    {
      /* 
       * When replying / forwarding, use the original message's
       * crypto system.  According to the documentation,
       * smime_is_default should be disregarded here.
       * 
       * Problem: At least with forwarding, this doesn't really
       * make much sense. Should we have an option to completely
       * disable individual mechanisms at run-time?
       */
      if (cur)
      {
	if ((WithCrypto & APPLICATION_PGP) && option (OPTCRYPTAUTOPGP) 
	    && (cur->security & APPLICATION_PGP))
	  msg->security |= APPLICATION_PGP;
	else if ((WithCrypto & APPLICATION_SMIME) && option (OPTCRYPTAUTOSMIME)
	    && (cur->security & APPLICATION_SMIME))
	  msg->security |= APPLICATION_SMIME;
      }

      /*
       * No crypto mechanism selected? Use availability + smime_is_default
       * for the decision. 
       */
      if (!(msg->security & (APPLICATION_SMIME | APPLICATION_PGP)))
      {
	if ((WithCrypto & APPLICATION_SMIME) && option (OPTCRYPTAUTOSMIME) 
	    && option (OPTSMIMEISDEFAULT))
	  msg->security |= APPLICATION_SMIME;
	else if ((WithCrypto & APPLICATION_PGP) && option (OPTCRYPTAUTOPGP))
	  msg->security |= APPLICATION_PGP;
	else if ((WithCrypto & APPLICATION_SMIME) && option (OPTCRYPTAUTOSMIME))
	  msg->security |= APPLICATION_SMIME;
      }
    }

    /* opportunistic encrypt relys on SMIME or PGP already being selected */
    if (option (OPTCRYPTOPPORTUNISTICENCRYPT))
    {
      /* If something has already enabled encryption, e.g. OPTCRYPTAUTOENCRYPT
       * or OPTCRYPTREPLYENCRYPT, then don't enable opportunistic encrypt for
       * the message.
       */
      if (! (msg->security & ENCRYPT))
      {
        msg->security |= OPPENCRYPT;
        crypt_opportunistic_encrypt(msg);
      }
    }

    /* No permissible mechanisms found.  Don't sign or encrypt. */
    if (!(msg->security & (APPLICATION_SMIME|APPLICATION_PGP)))
      msg->security = 0;
  }

  /* specify a default fcc.  if we are in batchmode, only save a copy of
   * the message if the value of $copy is yes or ask-yes */

  if (!fcc[0] && !(flags & (SENDPOSTPONEDFCC)) && (!(flags & SENDBATCH) || (quadoption (OPT_COPY) & 0x1)))
  {
    /* set the default FCC */
    if (!msg->env->from)
    {
      msg->env->from = mutt_default_from ();
      killfrom = 1; /* no need to check $use_from because if the user specified
		       a from address it would have already been set by now */
    }
    mutt_select_fcc (fcc, sizeof (fcc), msg);
    if (killfrom)
    {
      rfc822_free_address (&msg->env->from);
      killfrom = 0;
    }
  }

  
  mutt_update_encoding (msg->content);

  if (! (flags & (SENDMAILX | SENDBATCH)))
  {
main_loop:

    fcc_error = 0; /* reset value since we may have failed before */
    mutt_pretty_mailbox (fcc, sizeof (fcc));
    i = mutt_compose_menu (msg, fcc, sizeof (fcc), cur,
                           (flags & SENDNOFREEHEADER ? MUTT_COMPOSE_NOFREEHEADER : 0));
    if (i == -1)
    {
      /* abort */
      mutt_message _("Mail not sent.");
      goto cleanup;
    }
    else if (i == 1)
    {
      /* postpone the message until later. */
      if (msg->content->next)
	msg->content = mutt_make_multipart (msg->content);

      if (WithCrypto && option (OPTPOSTPONEENCRYPT) && PostponeEncryptAs
          && (msg->security & ENCRYPT))
      {
        int is_signed = msg->security & SIGN;
        if (is_signed)
          msg->security &= ~SIGN;

        pgpkeylist = safe_strdup (PostponeEncryptAs);
        if (mutt_protect (msg, pgpkeylist) == -1)
        {
          if (is_signed)
            msg->security |= SIGN;
          FREE (&pgpkeylist);
          msg->content = mutt_remove_multipart (msg->content);
          goto main_loop;
        }

        if (is_signed)
          msg->security |= SIGN;
        FREE (&pgpkeylist);
      }

      /*
       * make sure the message is written to the right part of a maildir 
       * postponed folder.
       */
      msg->read = 0; msg->old = 0;

      mutt_encode_descriptions (msg->content, 1);
      mutt_prepare_envelope (msg->env, 0);
      mutt_env_to_intl (msg->env, NULL, NULL);	/* Handle bad IDNAs the next time. */

      if (!Postponed || mutt_write_fcc (NONULL (Postponed), msg, (cur && (flags & SENDREPLY)) ? cur->env->message_id : NULL, 1, fcc) < 0)
      {
	msg->content = mutt_remove_multipart (msg->content);
	decode_descriptions (msg->content);
	mutt_unprepare_envelope (msg->env);
	goto main_loop;
      }
      mutt_update_num_postponed ();
      mutt_message _("Message postponed.");
      rv = 1;
      goto cleanup;
    }
  }

  if (!has_recips (msg->env->to) && !has_recips (msg->env->cc) &&
      !has_recips (msg->env->bcc))
  {
    if (! (flags & SENDBATCH))
    {
      mutt_error _("No recipients are specified!");
      goto main_loop;
    }
    else
    {
      puts _("No recipients were specified.");
      goto cleanup;
    }
  }

  if (mutt_env_to_intl (msg->env, &tag, &err))
  {
    mutt_error (_("Bad IDN in \"%s\": '%s'"), tag, err);
    FREE (&err);
    if (!(flags & SENDBATCH))
      goto main_loop;
    else 
      goto cleanup;
  }
  
  if (!msg->env->subject && ! (flags & SENDBATCH) &&
      (i = query_quadoption (OPT_SUBJECT, _("No subject, abort sending?"))) != MUTT_NO)
  {
    /* if the abort is automatic, print an error message */
    if (quadoption (OPT_SUBJECT) == MUTT_YES)
      mutt_error _("No subject specified.");
    goto main_loop;
  }

  if (msg->content->next)
    msg->content = mutt_make_multipart (msg->content);

  /* 
   * Ok, we need to do it this way instead of handling all fcc stuff in
   * one place in order to avoid going to main_loop with encoded "env"
   * in case of error.  Ugh.
   */

  mutt_encode_descriptions (msg->content, 1);
  
  /*
   * Make sure that clear_content and free_clear_content are
   * properly initialized -- we may visit this particular place in
   * the code multiple times, including after a failed call to
   * mutt_protect().
   */
  
  clear_content = NULL;
  free_clear_content = 0;
  
  if (WithCrypto)
  {
    if (msg->security & (ENCRYPT | SIGN))
    {
      /* save the decrypted attachments */
      clear_content = msg->content;
  
      if ((crypt_get_keys (msg, &pgpkeylist, 0) == -1) ||
          mutt_protect (msg, pgpkeylist) == -1)
      {
        msg->content = mutt_remove_multipart (msg->content);
        
	FREE (&pgpkeylist);
        
        decode_descriptions (msg->content);
        goto main_loop;
      }
      mutt_encode_descriptions (msg->content, 0);
    }
  
    /* 
     * at this point, msg->content is one of the following three things:
     * - multipart/signed.  In this case, clear_content is a child.
     * - multipart/encrypted.  In this case, clear_content exists
     *   independently
     * - application/pgp.  In this case, clear_content exists independently.
     * - something else.  In this case, it's the same as clear_content.
     */
  
    /* This is ugly -- lack of "reporting back" from mutt_protect(). */
    
    if (clear_content && (msg->content != clear_content)
        && (msg->content->parts != clear_content))
      free_clear_content = 1;
  }

  if (!option (OPTNOCURSES) && !(flags & SENDMAILX))
    mutt_message _("Sending message...");

  mutt_prepare_envelope (msg->env, 1);

  /* save a copy of the message, if necessary. */

  mutt_expand_path (fcc, sizeof (fcc));

  
  /* Don't save a copy when we are in batch-mode, and the FCC
   * folder is on an IMAP server: This would involve possibly lots
   * of user interaction, which is not available in batch mode. 
   * 
   * Note: A patch to fix the problems with the use of IMAP servers
   * from non-curses mode is available from Brendan Cully.  However, 
   * I'd like to think a bit more about this before including it.
   */

#ifdef USE_IMAP
  if ((flags & SENDBATCH) && fcc[0] && mx_is_imap (fcc))
    fcc[0] = '\0';
#endif

  if (*fcc && mutt_strcmp ("/dev/null", fcc) != 0)
  {
    BODY *tmpbody = msg->content;
    BODY *save_sig = NULL;
    BODY *save_parts = NULL;

    if (WithCrypto && (msg->security & (ENCRYPT | SIGN)) && option (OPTFCCCLEAR))
      msg->content = clear_content;

    /* check to see if the user wants copies of all attachments */
    if (query_quadoption (OPT_FCCATTACH, _("Save attachments in Fcc?")) != MUTT_YES &&
	msg->content->type == TYPEMULTIPART)
    {
      if (WithCrypto
          && (msg->security & (ENCRYPT | SIGN))
          && (mutt_strcmp (msg->content->subtype, "encrypted") == 0 ||
              mutt_strcmp (msg->content->subtype, "signed") == 0))
      {
	if (clear_content->type == TYPEMULTIPART)
	{
	  if(!(msg->security & ENCRYPT) && (msg->security & SIGN))
	  {
	    /* save initial signature and attachments */
	    save_sig = msg->content->parts->next;
	    save_parts = clear_content->parts->next;
	  }

	  /* this means writing only the main part */
	  msg->content = clear_content->parts;

	  if (mutt_protect (msg, pgpkeylist) == -1)
	  {
	    /* we can't do much about it at this point, so
	     * fallback to saving the whole thing to fcc
	     */
	    msg->content = tmpbody;
	    save_sig = NULL;
	    goto full_fcc;
	  }

	  save_content = msg->content;
	}
      }
      else
	msg->content = msg->content->parts;
    }

full_fcc:
    if (msg->content)
    {
      /* update received time so that when storing to a mbox-style folder
       * the From_ line contains the current time instead of when the
       * message was first postponed.
       */
      msg->received = time (NULL);
      if (mutt_write_fcc (fcc, msg, NULL, 0, NULL) == -1)
      {
	/*
	 * Error writing FCC, we should abort sending.
	 */
	fcc_error = 1;
      }
    }

    msg->content = tmpbody;

    if (WithCrypto && save_sig)
    {
      /* cleanup the second signature structures */
      if (save_content->parts)
      {
	mutt_free_body (&save_content->parts->next);
	save_content->parts = NULL;
      }
      mutt_free_body (&save_content);

      /* restore old signature and attachments */
      msg->content->parts->next = save_sig;
      msg->content->parts->parts->next = save_parts;
    }
    else if (WithCrypto && save_content)
    {
      /* destroy the new encrypted body. */
      mutt_free_body (&save_content);
    }

  }


  /*
   * Don't attempt to send the message if the FCC failed.  Just pretend
   * the send failed as well so we give the user a chance to fix the
   * error.
   */
  if (fcc_error || (i = send_message (msg)) < 0)
  {
    if (!(flags & SENDBATCH))
    {
      if (!WithCrypto)
        ;
      else if ((msg->security & ENCRYPT) || 
               ((msg->security & SIGN)
                && msg->content->type == TYPEAPPLICATION))
      {
	mutt_free_body (&msg->content); /* destroy PGP data */
	msg->content = clear_content;	/* restore clear text. */
      }
      else if ((msg->security & SIGN) && msg->content->type == TYPEMULTIPART)
      {
	mutt_free_body (&msg->content->parts->next);	     /* destroy sig */
	msg->content = mutt_remove_multipart (msg->content); 
      }

      msg->content = mutt_remove_multipart (msg->content);
      decode_descriptions (msg->content);
      mutt_unprepare_envelope (msg->env);
      goto main_loop;
    }
    else
    {
      puts _("Could not send the message.");
      goto cleanup;
    }
  }
  else if (!option (OPTNOCURSES) && ! (flags & SENDMAILX))
    mutt_message (i == 0 ? _("Mail sent.") : _("Sending in background."));

  if (WithCrypto && (msg->security & ENCRYPT))
    FREE (&pgpkeylist);
  
  if (WithCrypto && free_clear_content)
    mutt_free_body (&clear_content);

  /* set 'replied' flag only if the user didn't change/remove
     In-Reply-To: and References: headers during edit */
  if (flags & SENDREPLY)
  {
    if (cur && ctx)
      mutt_set_flag (ctx, cur, MUTT_REPLIED, is_reply (cur, msg));
    else if (!(flags & SENDPOSTPONED) && ctx && ctx->tagged)
    {
      for (i = 0; i < ctx->vcount; i++)
	if (ctx->hdrs[ctx->v2r[i]]->tagged)
	  mutt_set_flag (ctx, ctx->hdrs[ctx->v2r[i]], MUTT_REPLIED,
			 is_reply (ctx->hdrs[ctx->v2r[i]], msg));
    }
  }


  rv = 0;
  
cleanup:

  if (flags & SENDPOSTPONED)
  {
    if (WithCrypto & APPLICATION_PGP)
    {
      FREE (&PgpSignAs);
      PgpSignAs = pgp_signas;
    }
    if (WithCrypto & APPLICATION_SMIME)
    {
      FREE (&SmimeDefaultKey);
      SmimeDefaultKey = smime_default_key;
    }
  }
   
  safe_fclose (&tempfp);
  if (! (flags & SENDNOFREEHEADER))
    mutt_free_header (&msg);
  
  return rv;
}