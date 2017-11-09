static void mutt_update_v2r (ATTACH_CONTEXT *actx)
{
  int vindex, rindex, curlevel;

  vindex = rindex = 0;

  while (rindex < actx->idxlen)
  {
    actx->v2r[vindex++] = rindex;
    if (actx->idx[rindex]->content->collapsed)
    {
      curlevel = actx->idx[rindex]->level;
      do
        rindex++;
      while ((rindex < actx->idxlen) &&
             (actx->idx[rindex]->level > curlevel));
    }
    else
      rindex++;
  }

  actx->vcount = vindex;
}