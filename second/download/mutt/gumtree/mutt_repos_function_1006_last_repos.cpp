static short count_tagged (ATTACH_CONTEXT *actx)
{
  short count = 0;
  short i;
  
  for (i = 0; i < actx->idxlen; i++)
    if (actx->idx[i]->content->tagged)
      count++;
  
  return count;
}