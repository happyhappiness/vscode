static int is_parent (short i, ATTACH_CONTEXT *actx, BODY *cur)
{
  short level = actx->idx[i]->level;

  while ((++i < actx->idxlen) && actx->idx[i]->level > level)
  {
    if (actx->idx[i]->content == cur)
      return 1;
  }

  return 0;
}