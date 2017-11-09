void mutt_actx_add_fp (ATTACH_CONTEXT *actx, FILE *new_fp)
{
  int i;

  if (actx->fp_len == actx->fp_max)
  {
    actx->fp_max += 5;
    safe_realloc (&actx->fp_idx, sizeof (FILE *) * actx->fp_max);
    for (i = actx->fp_len; i < actx->fp_max; i++)
      actx->fp_idx[i] = NULL;
  }

  actx->fp_idx[actx->fp_len++] = new_fp;
}