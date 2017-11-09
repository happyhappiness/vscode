static void update_idx (MUTTMENU *menu, ATTACH_CONTEXT *actx, ATTACHPTR *new)
{
  new->level = (actx->idxlen > 0) ? actx->idx[actx->idxlen-1]->level : 0;
  if (actx->idxlen)
    actx->idx[actx->idxlen - 1]->content->next = new->content;
  new->content->aptr = new;
  mutt_actx_add_attach (actx, new);
  mutt_update_compose_menu (actx, menu, 0);
  menu->current = actx->vcount - 1;
}