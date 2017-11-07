static void
mutt_update_attach_index (BODY *cur, ATTACHPTR ***idxp,
				      short *idxlen, short *idxmax,
				      MUTTMENU *menu)
{
  ATTACHPTR **idx = *idxp;
  while (--(*idxlen) >= 0)
    idx[(*idxlen)]->content = NULL;
  *idxlen = 0;

  idx = *idxp = mutt_gen_attach_list (cur, -1, idx, idxlen, idxmax, 0, 0);
  
  menu->max  = *idxlen;
  menu->data = *idxp;

  if (menu->current >= menu->max)
    menu->current = menu->max - 1;
  menu_check_recenter (menu);
  menu->redraw |= REDRAW_INDEX;
  
}