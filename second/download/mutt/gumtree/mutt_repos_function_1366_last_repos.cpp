void mutt_view_attachments (HEADER *hdr)
{
  char helpstr[LONG_STRING];
  MUTTMENU *menu;
  BODY *cur = NULL;
  MESSAGE *msg;
  ATTACH_CONTEXT *actx;
  int flags = 0;
  int op = OP_NULL;
  int i;

  /* make sure we have parsed this message */
  mutt_parse_mime_message (Context, hdr);

  mutt_message_hook (Context, hdr, MUTT_MESSAGEHOOK);

  if ((msg = mx_open_message (Context, hdr->msgno)) == NULL)
    return;

  menu = mutt_new_menu (MENU_ATTACH);
  menu->title = _("Attachments");
  menu->make_entry = attach_entry;
  menu->tag = mutt_tag_attach;
  menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_ATTACH, AttachHelp);
  mutt_push_current_menu (menu);

  actx = safe_calloc (sizeof(ATTACH_CONTEXT), 1);
  actx->hdr = hdr;
  actx->root_fp = msg->fp;
  mutt_update_recvattach_menu (actx, menu, 1);

  FOREVER
  {
    if (op == OP_NULL)
      op = mutt_menuLoop (menu);
    switch (op)
    {
      case OP_ATTACH_VIEW_MAILCAP:
	mutt_view_attachment (CURATTACH->fp, CURATTACH->content, MUTT_MAILCAP,
			      hdr, actx);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_ATTACH_VIEW_TEXT:
	mutt_view_attachment (CURATTACH->fp, CURATTACH->content, MUTT_AS_TEXT,
			      hdr, actx);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_DISPLAY_HEADERS:
      case OP_VIEW_ATTACH:
        op = mutt_attach_display_loop (menu, op, hdr, actx, 1);
        menu->redraw = REDRAW_FULL;
        continue;

      case OP_ATTACH_COLLAPSE:
        if (!CURATTACH->content->parts)
        {
	  mutt_error _("There are no subparts to show!");
	  break;
	}
        attach_collapse (actx, menu);
        mutt_update_recvattach_menu (actx, menu, 0);
        break;

      case OP_FORGET_PASSPHRASE:
        crypt_forget_passphrase ();
        break;

      case OP_EXTRACT_KEYS:
        if ((WithCrypto & APPLICATION_PGP))
        {
          recvattach_extract_pgp_keys (actx, menu);
          menu->redraw = REDRAW_FULL;
        }
        break;

      case OP_CHECK_TRADITIONAL:
        if ((WithCrypto & APPLICATION_PGP) &&
            recvattach_pgp_check_traditional (actx, menu))
        {
	  hdr->security = crypt_query (cur);
	  menu->redraw = REDRAW_FULL;
	}
        break;

      case OP_PRINT:
	mutt_print_attachment_list (actx, CURATTACH->fp, menu->tagprefix,
                                    CURATTACH->content);
	break;

      case OP_PIPE:
	mutt_pipe_attachment_list (actx, CURATTACH->fp, menu->tagprefix,
                                   CURATTACH->content, 0);
	break;

      case OP_SAVE:
	mutt_save_attachment_list (actx, CURATTACH->fp, menu->tagprefix,
                                   CURATTACH->content, hdr, menu);

        if (!menu->tagprefix && option (OPTRESOLVE) && menu->current < menu->max - 1)
	  menu->current++;

        menu->redraw = REDRAW_MOTION_RESYNCH | REDRAW_FULL;
	break;

      case OP_DELETE:
	CHECK_READONLY;

#ifdef USE_POP
	if (Context->magic == MUTT_POP)
	{
	  mutt_flushinp ();
	  mutt_error _("Can't delete attachment from POP server.");
	  break;
	}
#endif

        if (WithCrypto && (hdr->security & ENCRYPT))
        {
          mutt_message _(
            "Deletion of attachments from encrypted messages is unsupported.");
          break;
        }
        if (WithCrypto && (hdr->security & (SIGN | PARTSIGN)))
        {
          mutt_message _(
            "Deletion of attachments from signed messages may invalidate the signature.");
        }
        if (!menu->tagprefix)
        {
          if (CURATTACH->parent_type == TYPEMULTIPART)
          {
            CURATTACH->content->deleted = 1;
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
            if (actx->idx[x]->content->tagged)
            {
              if (actx->idx[x]->parent_type == TYPEMULTIPART)
              {
                actx->idx[x]->content->deleted = 1;
                menu->redraw = REDRAW_INDEX;
              }
              else
                mutt_message _(
                  "Only deletion of multipart attachments is supported.");
            }
          }
        }
        break;

      case OP_UNDELETE:
       CHECK_READONLY;
       if (!menu->tagprefix)
       {
	 CURATTACH->content->deleted = 0;
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
	   if (actx->idx[x]->content->tagged)
	   {
	     actx->idx[x]->content->deleted = 0;
	     menu->redraw = REDRAW_INDEX;
	   }
	 }
       }
       break;

      case OP_RESEND:
        CHECK_ATTACH;
        mutt_attach_resend (CURATTACH->fp, hdr, actx,
                            menu->tagprefix ? NULL : CURATTACH->content);
        menu->redraw = REDRAW_FULL;
      	break;

      case OP_BOUNCE_MESSAGE:
        CHECK_ATTACH;
        mutt_attach_bounce (CURATTACH->fp, hdr, actx,
                            menu->tagprefix ? NULL : CURATTACH->content);
        menu->redraw = REDRAW_FULL;
      	break;

      case OP_FORWARD_MESSAGE:
        CHECK_ATTACH;
        mutt_attach_forward (CURATTACH->fp, hdr, actx,
			     menu->tagprefix ? NULL : CURATTACH->content);
        menu->redraw = REDRAW_FULL;
        break;

      case OP_REPLY:
      case OP_GROUP_REPLY:
      case OP_LIST_REPLY:

        CHECK_ATTACH;

        flags = SENDREPLY |
	  (op == OP_GROUP_REPLY ? SENDGROUPREPLY : 0) |
	  (op == OP_LIST_REPLY ? SENDLISTREPLY : 0);
        mutt_attach_reply (CURATTACH->fp, hdr, actx,
			   menu->tagprefix ? NULL : CURATTACH->content, flags);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_EDIT_TYPE:
        recvattach_edit_content_type (actx, menu, hdr);
        menu->redraw |= REDRAW_INDEX;
	break;

      case OP_EXIT:
	mx_close_message (Context, &msg);

	hdr->attach_del = 0;
        for (i = 0; i < actx->idxlen; i++)
	  if (actx->idx[i]->content &&
              actx->idx[i]->content->deleted)
          {
	    hdr->attach_del = 1;
            break;
          }
	if (hdr->attach_del)
	  hdr->changed = 1;

        mutt_free_attach_context (&actx);

        mutt_pop_current_menu (menu);
	mutt_menuDestroy  (&menu);
	return;
    }

    op = OP_NULL;
  }

  /* not reached */
}