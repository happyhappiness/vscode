static int
internal_function
sift_states_iter_mb (const re_match_context_t *mctx, re_sift_context_t *sctx,
		     int node_idx, int str_idx, int max_str_idx)
{
  const re_dfa_t *const dfa = mctx->dfa;
  int naccepted;
  /* Check the node can accept `multi byte'.  */
  naccepted = check_node_accept_bytes (dfa, node_idx, &mctx->input, str_idx);
  if (naccepted > 0 && str_idx + naccepted <= max_str_idx &&
      !STATE_NODE_CONTAINS (sctx->sifted_states[str_idx + naccepted],
			    dfa->nexts[node_idx]))
    /* The node can't accept the `multi byte', or the
       destination was already thrown away, then the node
       couldn't accept the current input `multi byte'.   */
    naccepted = 0;
  /* Otherwise, it is sure that the node could accept
     `naccepted' bytes input.  */
  return naccepted;
}