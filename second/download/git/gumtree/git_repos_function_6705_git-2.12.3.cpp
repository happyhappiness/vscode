static void
internal_function
match_ctx_clean (re_match_context_t *mctx)
{
  int st_idx;
  for (st_idx = 0; st_idx < mctx->nsub_tops; ++st_idx)
    {
      int sl_idx;
      re_sub_match_top_t *top = mctx->sub_tops[st_idx];
      for (sl_idx = 0; sl_idx < top->nlasts; ++sl_idx)
	{
	  re_sub_match_last_t *last = top->lasts[sl_idx];
	  re_free (last->path.array);
	  re_free (last);
	}
      re_free (top->lasts);
      if (top->path)
	{
	  re_free (top->path->array);
	  re_free (top->path);
	}
      free (top);
    }

  mctx->nsub_tops = 0;
  mctx->nbkref_ents = 0;
}