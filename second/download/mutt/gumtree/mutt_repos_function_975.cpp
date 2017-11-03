static int is_parent (short i, ATTACHPTR **idx, short idxlen, BODY *cur)
{
  short level = idx[i]->level;

  while ((++i < idxlen) && idx[i]->level > level)
  {
    if (idx[i]->content == cur)
      return 1;
  }

  return 0;
}