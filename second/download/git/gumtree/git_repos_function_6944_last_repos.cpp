static int
internal_function
check_halt_node_context (const re_dfa_t *dfa, int node, unsigned int context)
{
  re_token_type_t type = dfa->nodes[node].type;
  unsigned int constraint = dfa->nodes[node].constraint;
  if (type != END_OF_RE)
    return 0;
  if (!constraint)
    return 1;
  if (NOT_SATISFY_NEXT_CONSTRAINT (constraint, context))
    return 0;
  return 1;
}