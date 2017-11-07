static void update_idx (MUTTMENU *menu, ATTACHPTR **idx, short idxlen)
{
  idx[idxlen]->level = (idxlen > 0) ? idx[idxlen-1]->level : 0;
  if (idxlen)
    idx[idxlen - 1]->content->next = idx[idxlen]->content;
  idx[idxlen]->content->aptr = idx[idxlen];
  menu->current = idxlen++;
  mutt_update_tree (idx, idxlen);
  menu->max = idxlen;
  return;
}