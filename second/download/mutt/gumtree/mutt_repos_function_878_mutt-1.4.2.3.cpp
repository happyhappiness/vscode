void mutt_view_attachments (HEADER *hdr)
{



#ifdef HAVE_PGP
  int pgp = 0;
#endif



  char helpstr[SHORT_STRING];
  MUTTMENU *menu;
  BODY *cur;
  MESSAGE *msg;
  FILE *fp;
  ATTACHPTR **idx = NULL;
  short idxlen = 0;
  short idxmax = 0;
  int flags = 0;
  int op = OP_NULL;
  
  /* make sure we have parsed this message */
  mutt_parse_mime_message (Context, hdr);

  mutt_message_hook (Context, hdr, M_MESSAGEHOOK);
  
  if ((msg = mx_open_message (Context, hdr->msgno)) == NULL)
    return;



#ifdef HAVE_PGP
  if((hdr->pgp & PGPENCRYPT) && !pgp_valid_passphrase())
  {
    mx_close_message (&msg);
    return;
  }
  
  if ((hdr->pgp & PGPENCRYPT) && mutt_is_multipart_encrypted(hdr->content))
  {
    if (pgp_decrypt_mime (msg->fp, &fp, hdr->content, &cur))
    {
      mx_close_message (&msg);
      return;
    }
    pgp = 1;
  }
  else
#endif /* HAVE_PGP */
  {
    fp = msg->fp;
    cur = hdr->content;
  }

  menu = mutt_new_menu ();
  menu->menu = MENU_ATTACH;
  menu->title = _("Attachments");
  menu->make_entry = attach_entry;
  menu->tag = mutt_tag_attach;
  menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_ATTACH, AttachHelp);

  mutt_attach_init (cur);
  attach_collapse (cur, 0, 1, 0);
  mutt_update_attach_index (cur, &idx, &idxlen, &idxmax, menu);

  FOREVER
  {
    if (op == OP_NULL)
      op = mutt_menuLoop (menu);
    switch (op)
    {
      case OP_ATTACH_VIEW_MAILCAP:
	mutt_view_attachment (fp, idx[menu->current]->content, M_MAILCAP,
			      hdr, idx, idxlen);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_ATTACH_VIEW_TEXT:
	mutt_view_attachment (fp, idx[menu->current]->content, M_AS_TEXT,
			      hdr, idx, idxlen);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_DISPLAY_HEADERS:
      case OP_VIEW_ATTACH:
        op = mutt_attach_display_loop (menu, op, fp, hdr, cur, &idx, &idxlen, &idxmax, 1);
        menu->redraw = REDRAW_FULL;
        continue;

      case OP_ATTACH_COLLAPSE:
        if (!idx[menu->current]->content->parts)
        {
	  mutt_error _("There are no subparts to show!");
	  break;
	}
        if (!idx[menu->current]->content->collapsed)
	  attach_collapse (idx[menu->current]->content, 1, 0, 1);
        else
	  attach_collapse (idx[menu->current]->content, 0, 1, 1);
        mutt_update_attach_index (cur, &idx, &idxlen, &idxmax, menu);
        break;
      

#ifdef HAVE_PGP
      case OP_FORGET_PASSPHRASE:
        mutt_forget_passphrase ();
        break;
      
      case OP_EXTRACT_KEYS:
        pgp_extract_keys_from_attachment_list (fp, menu->tagprefix, 
		  menu->tagprefix ? cur : idx[menu->current]->content);
        menu->redraw = REDRAW_FULL;
        break;
      
      case OP_CHECK_TRADITIONAL:
        if (pgp_check_traditional (fp, menu->tagprefix ? cur : idx[menu->current]->content,
				   menu->tagprefix))
        {
	  hdr->pgp = pgp_query (cur);
	  menu->redraw = REDRAW_FULL;
	}
        break;
#endif
      


      case OP_PRINT:
	mutt_print_attachment_list (fp, menu->tagprefix, 
		  menu->tagprefix ? cur : idx[menu->current]->content);
	break;

      case OP_PIPE:
	mutt_pipe_attachment_list (fp, menu->tagprefix, 
		  menu->tagprefix ? cur : idx[menu->current]->content, 0);
	break;

      case OP_SAVE:
	mutt_save_attachment_list (fp, menu->tagprefix, 
		  menu->tagprefix ?  cur : idx[menu->current]->content, hdr);

        if (option (OPTRESOLVE) && menu->current < menu->max - 1)
	  menu->current++;
      
        menu->redraw = REDRAW_MOTION_RESYNCH | REDRAW_FULL;
	break;

      case OP_DELETE:
	CHECK_READONLY;

#ifdef USE_POP
	if (Context->magic == M_POP)
	{
	  mutt_flushinp ();
	  mutt_error _("Can't delete attachment from POP server.");
	  break;
	}
#endif



#ifdef HAVE_PGP
        if (hdr->pgp)
        {
	  mutt_message _(
	    "Deletion of attachments from PGP messages is unsupported.");
	}
        else
#endif
        {
	  if (!menu->tagprefix)
	  {
	    if (idx[menu->current]->parent_type == TYPEMULTIPART)
	    {
	      idx[menu->current]->content->deleted = 1;
	      if (option (OPTRESOLVE) && menu->current < menu->max - 1)
	      {
		menu->current++;
		menu->redraw = REDRAW_MOTION_RESYNCH;
	      }
	      else
		menu->redraw = REDRAW_CURRENT;
	    }
	    else
	      mutt_message _(
	        "Only deletion of multipart attachments is supported.");
	  }
	  else
	  {
	    int x;

	    for (x = 0; x < menu->max; x++)
	    {
	      if (idx[x]->content->tagged)
	      {
		if (idx[x]->parent_type == TYPEMULTIPART)
		{
		  idx[x]->content->deleted = 1;
		  menu->redraw = REDRAW_INDEX;
		}
		else
		  mutt_message _(
		    "Only deletion of multipart attachments is supported.");
	      }
	    }
	  }
	}
        break;

      case OP_UNDELETE:
       CHECK_READONLY;
       if (!menu->tagprefix)
       {
	 idx[menu->current]->content->deleted = 0;
	 if (option (OPTRESOLVE) && menu->current < menu->max - 1)
	 {
	   menu->current++;
	   menu->redraw = REDRAW_MOTION_RESYNCH;
	 }
	 else
	   menu->redraw = REDRAW_CURRENT;
       }
       else
       {
	 int x;

	 for (x = 0; x < menu->max; x++)
	 {
	   if (idx[x]->content->tagged)
	   {
	     idx[x]->content->deleted = 0;
	     menu->redraw = REDRAW_INDEX;
	   }
	 }
       }
       break;

      case OP_RESEND:
        CHECK_ATTACH;
        mutt_attach_resend (fp, hdr, idx, idxlen,
			     menu->tagprefix ? NULL : idx[menu->current]->content);
        menu->redraw = REDRAW_FULL;
      	break;
      
      case OP_BOUNCE_MESSAGE:
        CHECK_ATTACH;
        mutt_attach_bounce (fp, hdr, idx, idxlen,
			     menu->tagprefix ? NULL : idx[menu->current]->content);
        menu->redraw = REDRAW_FULL;
      	break;

      case OP_FORWARD_MESSAGE:
        CHECK_ATTACH;
        mutt_attach_forward (fp, hdr, idx, idxlen,
			     menu->tagprefix ? NULL : idx[menu->current]->content);
        menu->redraw = REDRAW_FULL;
        break;
      
      case OP_REPLY:
      case OP_GROUP_REPLY:
      case OP_LIST_REPLY:

        CHECK_ATTACH;
      
        flags = SENDREPLY | 
	  (op == OP_GROUP_REPLY ? SENDGROUPREPLY : 0) |
	  (op == OP_LIST_REPLY ? SENDLISTREPLY : 0);
        mutt_attach_reply (fp, hdr, idx, idxlen, 
			   menu->tagprefix ? NULL : idx[menu->current]->content, flags);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_EDIT_TYPE:
	mutt_edit_content_type (hdr, idx[menu->current]->content, fp);
        mutt_update_attach_index (cur, &idx, &idxlen, &idxmax, menu);
	break;

      case OP_EXIT:
	mx_close_message (&msg);
	hdr->attach_del = 0;
	while (idxmax-- > 0)
	{
	  if (!idx[idxmax])
	    continue;
	  if (idx[idxmax]->content && idx[idxmax]->content->deleted)
	    hdr->attach_del = 1;
	  safe_free ((void **) &idx[idxmax]->tree);
	  safe_free ((void **) &idx[idxmax]);
	}
	if (hdr->attach_del)
	  hdr->changed = 1;
	safe_free ((void **) &idx);
	idxmax = 0;



#ifdef HAVE_PGP
	if (pgp)
	{
	  fclose (fp);
	  mutt_free_body (&cur);
	}
#endif /* HAVE_PGP */



	mutt_menuDestroy  (&menu);
	return;
    }

    op = OP_NULL;
  }

  /* not reached */
}