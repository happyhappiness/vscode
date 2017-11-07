int
mutt_attach_display_loop (MUTTMENU *menu, int op, FILE *fp, HEADER *hdr,
			  BODY *cur, ATTACHPTR ***idxp, short *idxlen, short *idxmax,
			  int recv)
{
  ATTACHPTR **idx = *idxp;
#if 0
  int old_optweed = option (OPTWEED);
  set_option (OPTWEED);
#endif
  
  do
  {
    switch (op)
    {
      case OP_DISPLAY_HEADERS:
	toggle_option (OPTWEED);
	/* fall through */

      case OP_VIEW_ATTACH:
	op = mutt_view_attachment (fp, idx[menu->current]->content, MUTT_REGULAR,
				   hdr, idx, *idxlen);
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
	mutt_edit_content_type (hdr, idx[menu->current]->content, fp);
        if (idxmax)
        {
	  mutt_update_attach_index (cur, idxp, idxlen, idxmax, menu);
	  idx = *idxp;
	}
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