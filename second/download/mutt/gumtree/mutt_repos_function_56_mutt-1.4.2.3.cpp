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

#ifdef HAVE_PGP
  BODY *save_content = NULL;
  BODY *clear_content = NULL;
  char *pgpkeylist = NULL;
  /* save current value of "pgp_sign_as" */
  char *signas = NULL;
#endif

  int rv = -1;
  
  if (!flags && !msg && quadoption (OPT_RECALL) != M_NO &&
      mutt_num_postponed (1))
  {
    /* If the user is composing a new message, check to see if there
     * are any postponed messages first.
     */
    if ((i = query_quadoption (OPT_RECALL, _("Recall postponed message?"))) == -1)
      return rv;

    if(i == M_YES)
      flags |= SENDPOSTPONED;
  }
  
  
#ifdef HAVE_PGP
  if (flags & SENDPOSTPONED)
    signas = safe_strdup(PgpSignAs);
#endif /* HAVE_PGP */

  if (msg)
  {
    mutt_expand_aliases_env (msg->env);
  }
  else
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

  if (! (flags & (SENDKEY | SENDPOSTPONED | SENDRESEND)))
  {
    pbody = mutt_new_body ();
    pbody->next = msg->content; /* don't kill command-line attachments */
    msg->content = pbody;
    
    msg->content->type = TYPETEXT;
    msg->content->subtype = safe_strdup ("plain");
    msg->content->unlink = 1;
    msg->content->use_disp = 0;
    msg->content->disposition = DISPINLINE;
    if (option (OPTTEXTFLOWED))
      mutt_set_parameter ("format", "flowed", &msg->content->parameter);
    
    if (!tempfile)
    {
      mutt_mktemp (buffer);
      tempfp = safe_fopen (buffer, "w+");
      msg->content->filename = safe_strdup (buffer);
    }
    else
    {
      tempfp = safe_fopen (tempfile, "a+");
      msg->content->filename = safe_strdup (tempfile);
    }

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
     * line option */
    msg->env->from = set_reverse_name (cur->env);
  }

  if (!msg->env->from && option (OPTUSEFROM) && !(flags & (SENDPOSTPONED|SENDRESEND)))
    msg->env->from = mutt_default_from ();

  if (flags & SENDBATCH) 
  {
    mutt_copy_stream (stdin, tempfp);
    if (option (OPTHDRS))
    {
      process_user_recips (msg->env);
      process_user_header (msg->env);
    }
  }
  else if (! (flags & (SENDPOSTPONED|SENDRESEND)))
  {
    if ((flags & (SENDREPLY | SENDFORWARD)) && ctx &&
	envelope_defaults (msg->env, ctx, cur, flags) == -1)
      goto cleanup;

    if (option (OPTHDRS))
      process_user_recips (msg->env);

    if (! (flags & SENDMAILX) &&
	! (option (OPTAUTOEDIT) && option (OPTEDITHDRS)) &&
	! ((flags & SENDREPLY) && option (OPTFASTREPLY)))
    {
      if (edit_envelope (msg->env) == -1)
	goto cleanup;
    }

    /* the from address must be set here regardless of whether or not
     * $use_from is set so that the `~P' (from you) operator in send-hook
     * patterns will work.  if $use_from is unset, the from address is killed
     * after send-hooks are evaulated */

    if (!msg->env->from)
    {
      msg->env->from = mutt_default_from ();
      killfrom = 1;
    }

    /* change settings based upon recipients */
    
    mutt_message_hook (NULL, msg, M_SENDHOOK);

    if (killfrom)
    {
      rfc822_free_address (&msg->env->from);
      killfrom = 0;
    }

    if (option (OPTHDRS))
      process_user_header (msg->env);


    if (option (OPTSIGONTOP) && (! (flags & (SENDMAILX | SENDKEY)) && Editor && mutt_strcmp (Editor, "builtin") != 0))
      append_signature (tempfp);

    /* include replies/forwarded messages, unless we are given a template */
    if (!tempfile && (ctx || !(flags & (SENDREPLY|SENDFORWARD)))
	&& generate_body (tempfp, msg, flags, ctx, cur) == -1)
      goto cleanup;

    if (!option (OPTSIGONTOP) && (! (flags & (SENDMAILX | SENDKEY)) && Editor && mutt_strcmp (Editor, "builtin") != 0))
      append_signature (tempfp);

    /* 
     * this wants to be done _after_ generate_body, so message-hooks
     * can take effect.
     */

#ifdef HAVE_PGP
    if (! (flags & SENDMAILX))
    {
      if (option (OPTPGPAUTOSIGN))
	msg->pgp |= PGPSIGN;
      if (option (OPTPGPAUTOENCRYPT))
	msg->pgp |= PGPENCRYPT;
      
      msg->pgp |= set_pgp_flags (cur, ctx);
    }

#endif /* HAVE_PGP */
      



  }
  /* wait until now to set the real name portion of our return address so
     that $realname can be set in a send-hook */
  if (msg->env->from && !msg->env->from->personal && !(flags & (SENDRESEND|SENDPOSTPONED)))
    msg->env->from->personal = safe_strdup (Realname);



#ifdef HAVE_PGP
  if (! (flags & SENDKEY))
#endif
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

    /* If the this isn't a text message, look for a mailcap edit command */
    if(! (flags & SENDKEY))
    {
      if (mutt_needs_mailcap (msg->content))
	mutt_edit_attachment (msg->content);
      else if (!Editor || mutt_strcmp ("builtin", Editor) == 0)
	mutt_builtin_editor (msg->content->filename, msg, cur);
      else if (option (OPTEDITHDRS))
	mutt_edit_headers (Editor, msg->content->filename, msg, fcc, sizeof (fcc));
      else
	mutt_edit_file (Editor, msg->content->filename);
    }

    if (! (flags & (SENDPOSTPONED | SENDFORWARD | SENDKEY | SENDRESEND)))
    {
      if (stat (msg->content->filename, &st) == 0)
      {
	/* if the file was not modified, bail out now */
	if (mtime == st.st_mtime &&
	    query_quadoption (OPT_ABORT, _("Abort unmodified message?")) == M_YES)
	{
	  mutt_message _("Aborted unmodified message.");
	  goto cleanup;
	}
      }
      else
	mutt_perror (msg->content->filename);
    }
  }

  /* specify a default fcc.  if we are in batchmode, only save a copy of
   * the message if the value of $copy is yes or ask-yes */

  if (!fcc[0] && !(flags & (SENDPOSTPONED)) && (!(flags & SENDBATCH) || (quadoption (OPT_COPY) & 0x1)))
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

    mutt_pretty_mailbox (fcc);
    i = mutt_compose_menu (msg, fcc, sizeof (fcc), cur);
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

      /*
       * make sure the message is written to the right part of a maildir 
       * postponed folder.
       */
      msg->read = 0; msg->old = 0;

      encode_descriptions (msg->content, 1);
      mutt_prepare_envelope (msg->env, 0);

      if (!Postponed || mutt_write_fcc (NONULL (Postponed), msg, (cur && (flags & SENDREPLY)) ? cur->env->message_id : NULL, 1, fcc) < 0)
      {
	msg->content = mutt_remove_multipart (msg->content);
	decode_descriptions (msg->content);
	mutt_unprepare_envelope (msg->env);
	goto main_loop;
      }
      mutt_update_num_postponed ();
      mutt_message _("Message postponed.");
      goto cleanup;
    }
  }

  if (!msg->env->to && !msg->env->cc && !msg->env->bcc)
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

  if (!msg->env->subject && ! (flags & SENDBATCH) &&
      (i = query_quadoption (OPT_SUBJECT, _("No subject, abort sending?"))) != M_NO)
  {
    /* if the abort is automatic, print an error message */
    if (quadoption (OPT_SUBJECT) == M_YES)
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

  encode_descriptions (msg->content, 1);
  
#ifdef HAVE_PGP
  if (msg->pgp)
  {
    /* save the decrypted attachments */
    clear_content = msg->content;

    if ((pgp_get_keys (msg, &pgpkeylist) == -1) ||
	(pgp_protect (msg, pgpkeylist) == -1))
    {
      msg->content = mutt_remove_multipart (msg->content);
      
      if (pgpkeylist)
	FREE (&pgpkeylist);
      
      decode_descriptions (msg->content);
      goto main_loop;
    }
    encode_descriptions (msg->content, 0);
  }

  /* 
   * at this point, msg->content is one of the following three things:
   * - multipart/signed.  In this case, clear_content is a child.
   * - multipart/encrypted.  In this case, clear_content exists
   *   independently
   * - application/pgp.  In this case, clear_content exists independently.
   * - something else.  In this case, it's the same as clear_content.
   */

#endif /* HAVE_PGP */

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
#ifdef HAVE_PGP
    BODY *save_sig = NULL;
    BODY *save_parts = NULL;
#endif /* HAVE_PGP */

#ifdef HAVE_PGP
    if (msg->pgp && option (OPTFCCCLEAR))
      msg->content = clear_content;
#endif

    /* check to see if the user wants copies of all attachments */
    if (!option (OPTFCCATTACH) && msg->content->type == TYPEMULTIPART)
    {
#ifdef HAVE_PGP
      if (mutt_strcmp (msg->content->subtype, "encrypted") == 0 ||
	  mutt_strcmp (msg->content->subtype, "signed") == 0)
      {
	if (clear_content->type == TYPEMULTIPART)
	{
	  if (!(msg->pgp & PGPENCRYPT) && (msg->pgp & PGPSIGN))
	  {
	    /* save initial signature and attachments */
	    save_sig = msg->content->parts->next;
	    save_parts = clear_content->parts->next;
	  }

	  /* this means writing only the main part */
	  msg->content = clear_content->parts;

	  if (pgp_protect (msg, pgpkeylist) == -1)
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
#endif /* HAVE_PGP */
	msg->content = msg->content->parts;
    }

#ifdef HAVE_PGP
full_fcc:
#endif /* HAVE_PGP */
    if (msg->content)
    {
      /* update received time so that when storing to a mbox-style folder
       * the From_ line contains the current time instead of when the
       * message was first postponed.
       */
      msg->received = time (NULL);
      mutt_write_fcc (fcc, msg, NULL, 0, NULL);
    }

    msg->content = tmpbody;

#ifdef HAVE_PGP
    if (save_sig)
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
    else if (save_content)
    {
      /* destroy the new encrypted body. */
      mutt_free_body (&save_content);
    }
      
#endif /* HAVE_PGP */
  }


  if ((i = send_message (msg)) == -1)
  {
    if (!(flags & SENDBATCH))
    {
#ifdef HAVE_PGP
      if ((msg->pgp & PGPENCRYPT) || 
	  ((msg->pgp & PGPSIGN) && msg->content->type == TYPEAPPLICATION))
      {
	mutt_free_body (&msg->content); /* destroy PGP data */
	msg->content = clear_content;	/* restore clear text. */
      }
      else if ((msg->pgp & PGPSIGN) && msg->content->type == TYPEMULTIPART)
      {
	mutt_free_body (&msg->content->parts->next);		/* destroy sig */
	msg->content = mutt_remove_multipart (msg->content);	/* remove multipart */
      }
#endif
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

#ifdef HAVE_PGP
  if (msg->pgp & PGPENCRYPT)
  {
    /* cleanup structures from the first encryption */
    mutt_free_body (&clear_content);
    FREE (&pgpkeylist);
  }
#endif /* HAVE_PGP */

  if (flags & SENDREPLY)
  {
    if (cur && ctx)
      mutt_set_flag (ctx, cur, M_REPLIED, 1);
    else if (!(flags & SENDPOSTPONED) && ctx && ctx->tagged)
    {
      for (i = 0; i < ctx->vcount; i++)
	if (ctx->hdrs[ctx->v2r[i]]->tagged)
	  mutt_set_flag (ctx, ctx->hdrs[ctx->v2r[i]], M_REPLIED, 1);
    }
  }


  rv = 0;
  
cleanup:



#ifdef HAVE_PGP
  if (flags & SENDPOSTPONED)
  {
    
    if(signas)
    {
      safe_free((void **) &PgpSignAs);
      PgpSignAs = signas;
    }
  }
#endif /* HAVE_PGP */
   
  safe_fclose (&tempfp);
  mutt_free_header (&msg);
  
  return rv;

}