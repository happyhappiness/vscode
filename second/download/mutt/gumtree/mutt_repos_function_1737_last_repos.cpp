void mutt_actx_free_entries (ATTACH_CONTEXT *actx)
{
  int i;

  for (i = 0; i < actx->idxlen; i++)
  {
    if (actx->idx[i]->content)
      actx->idx[i]->content->aptr = NULL;
    FREE (&actx->idx[i]->tree);
    FREE (&actx->idx[i]);
  }
  actx->idxlen = 0;
  actx->vcount = 0;

  for (i = 0; i < actx->fp_len; i++)
    safe_fclose (&actx->fp_idx[i]);
  actx->fp_len = 0;

  for (i = 0; i < actx->body_len; i++)
    mutt_free_body (&actx->body_idx[i]);
  actx->body_len = 0;
}