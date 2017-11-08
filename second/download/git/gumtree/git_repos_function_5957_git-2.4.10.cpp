static int
internal_function
re_dfa_add_node (re_dfa_t *dfa, re_token_t token)
{
  if (BE (dfa->nodes_len >= dfa->nodes_alloc, 0))
    {
      size_t new_nodes_alloc = dfa->nodes_alloc * 2;
      int *new_nexts, *new_indices;
      re_node_set *new_edests, *new_eclosures;
      re_token_t *new_nodes;

      /* Avoid overflows in realloc.  */
      const size_t max_object_size = MAX (sizeof (re_token_t),
					  MAX (sizeof (re_node_set),
					       sizeof (int)));
      if (BE (SIZE_MAX / max_object_size < new_nodes_alloc, 0))
	return -1;

      new_nodes = re_realloc (dfa->nodes, re_token_t, new_nodes_alloc);
      if (BE (new_nodes == NULL, 0))
	return -1;
      dfa->nodes = new_nodes;
      new_nexts = re_realloc (dfa->nexts, int, new_nodes_alloc);
      new_indices = re_realloc (dfa->org_indices, int, new_nodes_alloc);
      new_edests = re_realloc (dfa->edests, re_node_set, new_nodes_alloc);
      new_eclosures = re_realloc (dfa->eclosures, re_node_set, new_nodes_alloc);
      if (BE (new_nexts == NULL || new_indices == NULL
	      || new_edests == NULL || new_eclosures == NULL, 0))
	return -1;
      dfa->nexts = new_nexts;
      dfa->org_indices = new_indices;
      dfa->edests = new_edests;
      dfa->eclosures = new_eclosures;
      dfa->nodes_alloc = new_nodes_alloc;
    }
  dfa->nodes[dfa->nodes_len] = token;
  dfa->nodes[dfa->nodes_len].constraint = 0;
#ifdef RE_ENABLE_I18N
  dfa->nodes[dfa->nodes_len].accept_mb =
    (token.type == OP_PERIOD && dfa->mb_cur_max > 1) || token.type == COMPLEX_BRACKET;
#endif
  dfa->nexts[dfa->nodes_len] = -1;
  re_node_set_init_empty (dfa->edests + dfa->nodes_len);
  re_node_set_init_empty (dfa->eclosures + dfa->nodes_len);
  return dfa->nodes_len++;
}