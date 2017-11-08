static int
internal_function
group_nodes_into_DFAstates (const re_dfa_t *dfa, const re_dfastate_t *state,
			    re_node_set *dests_node, bitset_t *dests_ch)
{
  reg_errcode_t err;
  int result;
  int i, j, k;
  int ndests; /* Number of the destinations from `state'.  */
  bitset_t accepts; /* Characters a node can accept.  */
  const re_node_set *cur_nodes = &state->nodes;
  bitset_empty (accepts);
  ndests = 0;

  /* For all the nodes belonging to `state',  */
  for (i = 0; i < cur_nodes->nelem; ++i)
    {
      re_token_t *node = &dfa->nodes[cur_nodes->elems[i]];
      re_token_type_t type = node->type;
      unsigned int constraint = node->constraint;

      /* Enumerate all single byte character this node can accept.  */
      if (type == CHARACTER)
	bitset_set (accepts, node->opr.c);
      else if (type == SIMPLE_BRACKET)
	{
	  bitset_merge (accepts, node->opr.sbcset);
	}
      else if (type == OP_PERIOD)
	{
#ifdef RE_ENABLE_I18N
	  if (dfa->mb_cur_max > 1)
	    bitset_merge (accepts, dfa->sb_char);
	  else
#endif
	    bitset_set_all (accepts);
	  if (!(dfa->syntax & RE_DOT_NEWLINE))
	    bitset_clear (accepts, '\n');
	  if (dfa->syntax & RE_DOT_NOT_NULL)
	    bitset_clear (accepts, '\0');
	}
#ifdef RE_ENABLE_I18N
      else if (type == OP_UTF8_PERIOD)
	{
	  memset (accepts, '\xff', sizeof (bitset_t) / 2);
	  if (!(dfa->syntax & RE_DOT_NEWLINE))
	    bitset_clear (accepts, '\n');
	  if (dfa->syntax & RE_DOT_NOT_NULL)
	    bitset_clear (accepts, '\0');
	}
#endif
      else
	continue;

      /* Check the `accepts' and sift the characters which are not
	 match it the context.  */
      if (constraint)
	{
	  if (constraint & NEXT_NEWLINE_CONSTRAINT)
	    {
	      bool accepts_newline = bitset_contain (accepts, NEWLINE_CHAR);
	      bitset_empty (accepts);
	      if (accepts_newline)
		bitset_set (accepts, NEWLINE_CHAR);
	      else
		continue;
	    }
	  if (constraint & NEXT_ENDBUF_CONSTRAINT)
	    {
	      bitset_empty (accepts);
	      continue;
	    }

	  if (constraint & NEXT_WORD_CONSTRAINT)
	    {
	      bitset_word_t any_set = 0;
	      if (type == CHARACTER && !node->word_char)
		{
		  bitset_empty (accepts);
		  continue;
		}
#ifdef RE_ENABLE_I18N
	      if (dfa->mb_cur_max > 1)
		for (j = 0; j < BITSET_WORDS; ++j)
		  any_set |= (accepts[j] &= (dfa->word_char[j] | ~dfa->sb_char[j]));
	      else
#endif
		for (j = 0; j < BITSET_WORDS; ++j)
		  any_set |= (accepts[j] &= dfa->word_char[j]);
	      if (!any_set)
		continue;
	    }
	  if (constraint & NEXT_NOTWORD_CONSTRAINT)
	    {
	      bitset_word_t any_set = 0;
	      if (type == CHARACTER && node->word_char)
		{
		  bitset_empty (accepts);
		  continue;
		}
#ifdef RE_ENABLE_I18N
	      if (dfa->mb_cur_max > 1)
		for (j = 0; j < BITSET_WORDS; ++j)
		  any_set |= (accepts[j] &= ~(dfa->word_char[j] & dfa->sb_char[j]));
	      else
#endif
		for (j = 0; j < BITSET_WORDS; ++j)
		  any_set |= (accepts[j] &= ~dfa->word_char[j]);
	      if (!any_set)
		continue;
	    }
	}

      /* Then divide `accepts' into DFA states, or create a new
	 state.  Above, we make sure that accepts is not empty.  */
      for (j = 0; j < ndests; ++j)
	{
	  bitset_t intersec; /* Intersection sets, see below.  */
	  bitset_t remains;
	  /* Flags, see below.  */
	  bitset_word_t has_intersec, not_subset, not_consumed;

	  /* Optimization, skip if this state doesn't accept the character.  */
	  if (type == CHARACTER && !bitset_contain (dests_ch[j], node->opr.c))
	    continue;

	  /* Enumerate the intersection set of this state and `accepts'.  */
	  has_intersec = 0;
	  for (k = 0; k < BITSET_WORDS; ++k)
	    has_intersec |= intersec[k] = accepts[k] & dests_ch[j][k];
	  /* And skip if the intersection set is empty.  */
	  if (!has_intersec)
	    continue;

	  /* Then check if this state is a subset of `accepts'.  */
	  not_subset = not_consumed = 0;
	  for (k = 0; k < BITSET_WORDS; ++k)
	    {
	      not_subset |= remains[k] = ~accepts[k] & dests_ch[j][k];
	      not_consumed |= accepts[k] = accepts[k] & ~dests_ch[j][k];
	    }

	  /* If this state isn't a subset of `accepts', create a
	     new group state, which has the `remains'. */
	  if (not_subset)
	    {
	      bitset_copy (dests_ch[ndests], remains);
	      bitset_copy (dests_ch[j], intersec);
	      err = re_node_set_init_copy (dests_node + ndests, &dests_node[j]);
	      if (BE (err != REG_NOERROR, 0))
		goto error_return;
	      ++ndests;
	    }

	  /* Put the position in the current group. */
	  result = re_node_set_insert (&dests_node[j], cur_nodes->elems[i]);
	  if (BE (result < 0, 0))
	    goto error_return;

	  /* If all characters are consumed, go to next node. */
	  if (!not_consumed)
	    break;
	}
      /* Some characters remain, create a new group. */
      if (j == ndests)
	{
	  bitset_copy (dests_ch[ndests], accepts);
	  err = re_node_set_init_1 (dests_node + ndests, cur_nodes->elems[i]);
	  if (BE (err != REG_NOERROR, 0))
	    goto error_return;
	  ++ndests;
	  bitset_empty (accepts);
	}
    }
  return ndests;
 error_return:
  for (j = 0; j < ndests; ++j)
    re_node_set_free (dests_node + j);
  return -1;
}