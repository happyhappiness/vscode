void mutt_sb_change_mailbox (int op)
{
  if (!option (OPTSIDEBAR))
    return;

  if (HilIndex < 0)	/* It'll get reset on the next draw */
    return;

  switch (op)
  {
    case OP_SIDEBAR_NEXT:
      if (! select_next ())
        return;
      break;
    case OP_SIDEBAR_NEXT_NEW:
      if (! select_next_new ())
        return;
      break;
    case OP_SIDEBAR_PAGE_DOWN:
      if (! select_page_down ())
        return;
      break;
    case OP_SIDEBAR_PAGE_UP:
      if (! select_page_up ())
        return;
      break;
    case OP_SIDEBAR_PREV:
      if (! select_prev ())
        return;
      break;
    case OP_SIDEBAR_PREV_NEW:
      if (! select_prev_new ())
        return;
      break;
    default:
      return;
  }
  SidebarNeedsRedraw = 1;
}