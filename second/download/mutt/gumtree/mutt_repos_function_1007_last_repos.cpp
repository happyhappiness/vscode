static short count_tagged_children (ATTACH_CONTEXT *actx, short i)
{
  short level = actx->idx[i]->level;
  short count = 0;

  while ((++i < actx->idxlen) && (level < actx->idx[i]->level))
    if (actx->idx[i]->content->tagged)
      count++;

  return count;
}