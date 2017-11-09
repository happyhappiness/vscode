static void mutt_update_recvattach_menu (ATTACH_CONTEXT *actx, MUTTMENU *menu, int init)
{
  if (init)
  {
    mutt_generate_recvattach_list (actx, actx->hdr, actx->hdr->content,
                                   actx->root_fp, -1, 0, 0);
    mutt_attach_init (actx);
    menu->data = actx;
  }

  mutt_update_tree (actx);

  menu->max  = actx->vcount;

  if (menu->current >= menu->max)
    menu->current = menu->max - 1;
  menu_check_recenter (menu);
  menu->redraw |= REDRAW_INDEX;
}