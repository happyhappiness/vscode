static short check_can_decode (ATTACH_CONTEXT *actx, BODY * cur)
{
  short i;

  if (cur)
    return mutt_can_decode (cur);

  for (i = 0; i < actx->idxlen; i++)
    if (actx->idx[i]->content->tagged && !mutt_can_decode (actx->idx[i]->content))
      return 0;

  return 1;
}