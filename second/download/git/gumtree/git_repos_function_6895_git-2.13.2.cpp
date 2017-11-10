static reg_errcode_t
internal_function
match_ctx_add_subtop (re_match_context_t *mctx, int node, int str_idx)
{
#ifdef DEBUG
  assert (mctx->sub_tops != NULL);
  assert (mctx->asub_tops > 0);
#endif
  if (BE (mctx->nsub_tops == mctx->asub_tops, 0))
    {
      int new_asub_tops = mctx->asub_tops * 2;
      re_sub_match_top_t **new_array = re_realloc (mctx->sub_tops,
						   re_sub_match_top_t *,
						   new_asub_tops);
      if (BE (new_array == NULL, 0))
	return REG_ESPACE;
      mctx->sub_tops = new_array;
      mctx->asub_tops = new_asub_tops;
    }
  mctx->sub_tops[mctx->nsub_tops] = calloc (1, sizeof (re_sub_match_top_t));
  if (BE (mctx->sub_tops[mctx->nsub_tops] == NULL, 0))
    return REG_ESPACE;
  mctx->sub_tops[mctx->nsub_tops]->node = node;
  mctx->sub_tops[mctx->nsub_tops++]->str_idx = str_idx;
  return REG_NOERROR;
}