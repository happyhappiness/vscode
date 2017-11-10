static re_dfastate_t *
internal_function
create_cd_newstate (const re_dfa_t *dfa, const re_node_set *nodes,
		    unsigned int context, unsigned int hash)
{
  int i, nctx_nodes = 0;
  reg_errcode_t err;
  re_dfastate_t *newstate;

  newstate = (re_dfastate_t *) calloc (sizeof (re_dfastate_t), 1);
  if (BE (newstate == NULL, 0))
    return NULL;
  err = re_node_set_init_copy (&newstate->nodes, nodes);
  if (BE (err != REG_NOERROR, 0))
    {
      re_free (newstate);
      return NULL;
    }

  newstate->context = context;
  newstate->entrance_nodes = &newstate->nodes;

  for (i = 0 ; i < nodes->nelem ; i++)
    {
      re_token_t *node = dfa->nodes + nodes->elems[i];
      re_token_type_t type = node->type;
      unsigned int constraint = node->constraint;

      if (type == CHARACTER && !constraint)
	continue;
#ifdef RE_ENABLE_I18N
      newstate->accept_mb |= node->accept_mb;
#endif /* RE_ENABLE_I18N */

      /* If the state has the halt node, the state is a halt state.  */
      if (type == END_OF_RE)
	newstate->halt = 1;
      else if (type == OP_BACK_REF)
	newstate->has_backref = 1;

      if (constraint)
	{
	  if (newstate->entrance_nodes == &newstate->nodes)
	    {
	      newstate->entrance_nodes = re_malloc (re_node_set, 1);
	      if (BE (newstate->entrance_nodes == NULL, 0))
		{
		  free_state (newstate);
		  return NULL;
		}
	      if (re_node_set_init_copy (newstate->entrance_nodes, nodes)
		  != REG_NOERROR)
		return NULL;
	      nctx_nodes = 0;
	      newstate->has_constraint = 1;
	    }

	  if (NOT_SATISFY_PREV_CONSTRAINT (constraint,context))
	    {
	      re_node_set_remove_at (&newstate->nodes, i - nctx_nodes);
	      ++nctx_nodes;
	    }
	}
    }
  err = register_state (dfa, newstate, hash);
  if (BE (err != REG_NOERROR, 0))
    {
      free_state (newstate);
      newstate = NULL;
    }
  return  newstate;
}