int
mutt_attach_display_loop (MUTTMENU *menu, int op, HEADER *hdr,
			  ATTACH_CONTEXT *actx, int recv)
{
  do
  {
    switch (op)
    {
      case OP_DISPLAY_HEADERS:
	toggle_option (OPTWEED);
	/* fall through */

      case OP_VIEW_ATTACH:
	op = mutt_view_attachment (CURATTACH->fp, CURATTACH->content, MUTT_REGULAR,
				   hdr, actx);
	break;

      case OP_NEXT_ENTRY:
      case OP_MAIN_NEXT_UNDELETED: /* hack */
	if (menu->current < menu->max - 1)
	{
	  menu->current++;
	  op = OP_VIEW_ATTACH;
	}
	else
	  op = OP_NULL;
	break;
      case OP_PREV_ENTRY:
      case OP_MAIN_PREV_UNDELETED: /* hack */
	if (menu->current > 0)
	{
	  menu->current--;
	  op = OP_VIEW_ATTACH;
	}
	else
	  op = OP_NULL;
	break;
      case OP_EDIT_TYPE:
	/* when we edit the content-type, we should redisplay the attachment
	   immediately */
        if (recv)
          recvattach_edit_content_type (actx, menu, hdr);
        else
          mutt_edit_content_type (hdr, CURATTACH->content, CURATTACH->fp);

        menu->redraw |= REDRAW_INDEX;
        op = OP_VIEW_ATTACH;
	break;
      /* functions which are passed through from the pager */
      case OP_CHECK_TRADITIONAL:
        if (!(WithCrypto & APPLICATION_PGP) || (hdr && hdr->security & PGP_TRADITIONAL_CHECKED))
        {
          op = OP_NULL;
          break;
        }
        /* fall through */
      case OP_ATTACH_COLLAPSE:
        if (recv)
          return op;
      default:
	op = OP_NULL;
    }
  }
  while (op != OP_NULL);

#if 0
  if (option (OPTWEED) != old_optweed)
    toggle_option (OPTWEED);
#endif
  return op;
}