static int
internal_function
check_halt_state_context (const re_match_context_t *mctx,
			  const re_dfastate_t *state, int idx)
{
  int i;
  unsigned int context;
#ifdef DEBUG
  assert (state->halt);
#endif
  context = re_string_context_at (&mctx->input, idx, mctx->eflags);
  for (i = 0; i < state->nodes.nelem; ++i)
    if (check_halt_node_context (mctx->dfa, state->nodes.elems[i], context))
      return state->nodes.elems[i];
  return 0;
}