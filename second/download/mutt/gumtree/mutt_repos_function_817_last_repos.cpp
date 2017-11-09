static void mutt_update_compose_menu (ATTACH_CONTEXT *actx, MUTTMENU *menu, int init)
{
  if (init)
  {
    mutt_gen_compose_attach_list (actx, actx->hdr->content, -1, 0);
    mutt_attach_init (actx);
    menu->data = actx;
  }

  mutt_update_tree (actx);

  menu->max = actx->vcount;
  if (menu->max)
  {
    if (menu->current >= menu->max)
      menu->current = menu->max - 1;
  }
  else
    menu->current = 0;

  menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
}