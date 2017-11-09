void mutt_free_attach_context (ATTACH_CONTEXT **pactx)
{
  ATTACH_CONTEXT *actx;

  if (!pactx || !*pactx)
    return;

  actx = *pactx;
  mutt_actx_free_entries (actx);
  FREE (&actx->idx);
  FREE (&actx->v2r);
  FREE (&actx->fp_idx);
  FREE (&actx->body_idx);
  FREE (pactx);  /* __FREE_CHECKED__ */
}