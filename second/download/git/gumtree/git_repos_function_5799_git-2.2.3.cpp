static void
internal_function
sift_ctx_init (re_sift_context_t *sctx, re_dfastate_t **sifted_sts,
	       re_dfastate_t **limited_sts, int last_node, int last_str_idx)
{
  sctx->sifted_states = sifted_sts;
  sctx->limited_states = limited_sts;
  sctx->last_node = last_node;
  sctx->last_str_idx = last_str_idx;
  re_node_set_init_empty (&sctx->limits);
}