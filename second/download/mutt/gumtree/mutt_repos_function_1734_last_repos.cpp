void mutt_actx_add_attach (ATTACH_CONTEXT *actx, ATTACHPTR *attach)
{
  int i;

  if (actx->idxlen == actx->idxmax)
  {
    actx->idxmax += 5;
    safe_realloc (&actx->idx, sizeof (ATTACHPTR *) * actx->idxmax);
    safe_realloc (&actx->v2r, sizeof (short) * actx->idxmax);
    for (i = actx->idxlen; i < actx->idxmax; i++)
      actx->idx[i] = NULL;
  }

  actx->idx[actx->idxlen++] = attach;
}