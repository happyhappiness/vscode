static void
internal_function
match_ctx_free (re_match_context_t *mctx)
{
  /* First, free all the memory associated with MCTX->SUB_TOPS.  */
  match_ctx_clean (mctx);
  re_free (mctx->sub_tops);
  re_free (mctx->bkref_ents);
}