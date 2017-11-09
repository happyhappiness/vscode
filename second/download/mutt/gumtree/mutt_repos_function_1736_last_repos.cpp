void mutt_actx_add_body (ATTACH_CONTEXT *actx, BODY *new_body)
{
  int i;

  if (actx->body_len == actx->body_max)
  {
    actx->body_max += 5;
    safe_realloc (&actx->body_idx, sizeof (BODY *) * actx->body_max);
    for (i = actx->body_len; i < actx->body_max; i++)
      actx->body_idx[i] = NULL;
  }

  actx->body_idx[actx->body_len++] = new_body;
}