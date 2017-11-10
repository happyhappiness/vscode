static void
free_state (re_dfastate_t *state)
{
  re_node_set_free (&state->non_eps_nodes);
  re_node_set_free (&state->inveclosure);
  if (state->entrance_nodes != &state->nodes)
    {
      re_node_set_free (state->entrance_nodes);
      re_free (state->entrance_nodes);
    }
  re_node_set_free (&state->nodes);
  re_free (state->word_trtable);
  re_free (state->trtable);
  re_free (state);
}