static int
internal_function
build_trtable (const re_dfa_t *dfa, re_dfastate_t *state)
{
  reg_errcode_t err;
  int i, j, ch, need_word_trtable = 0;
  bitset_word_t elem, mask;
  bool dests_node_malloced = false;
  bool dest_states_malloced = false;
  int ndests; /* Number of the destination states from `state'.  */
  re_dfastate_t **trtable;
  re_dfastate_t **dest_states = NULL, **dest_states_word, **dest_states_nl;
  re_node_set follows, *dests_node;
  bitset_t *dests_ch;
  bitset_t acceptable;

  struct dests_alloc
  {
    re_node_set dests_node[SBC_MAX];
    bitset_t dests_ch[SBC_MAX];
  } *dests_alloc;

  /* We build DFA states which corresponds to the destination nodes
     from `state'.  `dests_node[i]' represents the nodes which i-th
     destination state contains, and `dests_ch[i]' represents the
     characters which i-th destination state accepts.  */
#ifdef HAVE_ALLOCA
  if (__libc_use_alloca (sizeof (struct dests_alloc)))
    dests_alloc = (struct dests_alloc *) alloca (sizeof (struct dests_alloc));
  else
#endif
    {
      dests_alloc = re_malloc (struct dests_alloc, 1);
      if (BE (dests_alloc == NULL, 0))
	return 0;
      dests_node_malloced = true;
    }
  dests_node = dests_alloc->dests_node;
  dests_ch = dests_alloc->dests_ch;

  /* Initialize transiton table.  */
  state->word_trtable = state->trtable = NULL;

  /* At first, group all nodes belonging to `state' into several
     destinations.  */
  ndests = group_nodes_into_DFAstates (dfa, state, dests_node, dests_ch);
  if (BE (ndests <= 0, 0))
    {
      if (dests_node_malloced)
	free (dests_alloc);
      /* Return 0 in case of an error, 1 otherwise.  */
      if (ndests == 0)
	{
	  state->trtable = (re_dfastate_t **)
	    calloc (sizeof (re_dfastate_t *), SBC_MAX);
	  return 1;
	}
      return 0;
    }

  err = re_node_set_alloc (&follows, ndests + 1);
  if (BE (err != REG_NOERROR, 0))
    goto out_free;

  /* Avoid arithmetic overflow in size calculation.  */
  if (BE ((((SIZE_MAX - (sizeof (re_node_set) + sizeof (bitset_t)) * SBC_MAX)
	    / (3 * sizeof (re_dfastate_t *)))
	   < ndests),
	  0))
    goto out_free;

#ifdef HAVE_ALLOCA
  if (__libc_use_alloca ((sizeof (re_node_set) + sizeof (bitset_t)) * SBC_MAX
			 + ndests * 3 * sizeof (re_dfastate_t *)))
    dest_states = (re_dfastate_t **)
      alloca (ndests * 3 * sizeof (re_dfastate_t *));
  else
#endif
    {
      dest_states = (re_dfastate_t **)
	malloc (ndests * 3 * sizeof (re_dfastate_t *));
      if (BE (dest_states == NULL, 0))
	{
out_free:
	  if (dest_states_malloced)
	    free (dest_states);
	  re_node_set_free (&follows);
	  for (i = 0; i < ndests; ++i)
	    re_node_set_free (dests_node + i);
	  if (dests_node_malloced)
	    free (dests_alloc);
	  return 0;
	}
      dest_states_malloced = true;
    }
  dest_states_word = dest_states + ndests;
  dest_states_nl = dest_states_word + ndests;
  bitset_empty (acceptable);

  /* Then build the states for all destinations.  */
  for (i = 0; i < ndests; ++i)
    {
      int next_node;
      re_node_set_empty (&follows);
      /* Merge the follows of this destination states.  */
      for (j = 0; j < dests_node[i].nelem; ++j)
	{
	  next_node = dfa->nexts[dests_node[i].elems[j]];
	  if (next_node != -1)
	    {
	      err = re_node_set_merge (&follows, dfa->eclosures + next_node);
	      if (BE (err != REG_NOERROR, 0))
		goto out_free;
	    }
	}
      dest_states[i] = re_acquire_state_context (&err, dfa, &follows, 0);
      if (BE (dest_states[i] == NULL && err != REG_NOERROR, 0))
	goto out_free;
      /* If the new state has context constraint,
	 build appropriate states for these contexts.  */
      if (dest_states[i]->has_constraint)
	{
	  dest_states_word[i] = re_acquire_state_context (&err, dfa, &follows,
							  CONTEXT_WORD);
	  if (BE (dest_states_word[i] == NULL && err != REG_NOERROR, 0))
	    goto out_free;

	  if (dest_states[i] != dest_states_word[i] && dfa->mb_cur_max > 1)
	    need_word_trtable = 1;

	  dest_states_nl[i] = re_acquire_state_context (&err, dfa, &follows,
							CONTEXT_NEWLINE);
	  if (BE (dest_states_nl[i] == NULL && err != REG_NOERROR, 0))
	    goto out_free;
 	}
      else
	{
	  dest_states_word[i] = dest_states[i];
	  dest_states_nl[i] = dest_states[i];
	}
      bitset_merge (acceptable, dests_ch[i]);
    }

  if (!BE (need_word_trtable, 0))
    {
      /* We don't care about whether the following character is a word
	 character, or we are in a single-byte character set so we can
	 discern by looking at the character code: allocate a
	 256-entry transition table.  */
      trtable = state->trtable =
	(re_dfastate_t **) calloc (sizeof (re_dfastate_t *), SBC_MAX);
      if (BE (trtable == NULL, 0))
	goto out_free;

      /* For all characters ch...:  */
      for (i = 0; i < BITSET_WORDS; ++i)
	for (ch = i * BITSET_WORD_BITS, elem = acceptable[i], mask = 1;
	     elem;
	     mask <<= 1, elem >>= 1, ++ch)
	  if (BE (elem & 1, 0))
	    {
	      /* There must be exactly one destination which accepts
		 character ch.  See group_nodes_into_DFAstates.  */
	      for (j = 0; (dests_ch[j][i] & mask) == 0; ++j)
		;

	      /* j-th destination accepts the word character ch.  */
	      if (dfa->word_char[i] & mask)
		trtable[ch] = dest_states_word[j];
	      else
		trtable[ch] = dest_states[j];
	    }
    }
  else
    {
      /* We care about whether the following character is a word
	 character, and we are in a multi-byte character set: discern
	 by looking at the character code: build two 256-entry
	 transition tables, one starting at trtable[0] and one
	 starting at trtable[SBC_MAX].  */
      trtable = state->word_trtable =
	(re_dfastate_t **) calloc (sizeof (re_dfastate_t *), 2 * SBC_MAX);
      if (BE (trtable == NULL, 0))
	goto out_free;

      /* For all characters ch...:  */
      for (i = 0; i < BITSET_WORDS; ++i)
	for (ch = i * BITSET_WORD_BITS, elem = acceptable[i], mask = 1;
	     elem;
	     mask <<= 1, elem >>= 1, ++ch)
	  if (BE (elem & 1, 0))
	    {
	      /* There must be exactly one destination which accepts
		 character ch.  See group_nodes_into_DFAstates.  */
	      for (j = 0; (dests_ch[j][i] & mask) == 0; ++j)
		;

	      /* j-th destination accepts the word character ch.  */
	      trtable[ch] = dest_states[j];
	      trtable[ch + SBC_MAX] = dest_states_word[j];
	    }
    }

  /* new line */
  if (bitset_contain (acceptable, NEWLINE_CHAR))
    {
      /* The current state accepts newline character.  */
      for (j = 0; j < ndests; ++j)
	if (bitset_contain (dests_ch[j], NEWLINE_CHAR))
	  {
	    /* k-th destination accepts newline character.  */
	    trtable[NEWLINE_CHAR] = dest_states_nl[j];
	    if (need_word_trtable)
	      trtable[NEWLINE_CHAR + SBC_MAX] = dest_states_nl[j];
	    /* There must be only one destination which accepts
	       newline.  See group_nodes_into_DFAstates.  */
	    break;
	  }
    }

  if (dest_states_malloced)
    free (dest_states);

  re_node_set_free (&follows);
  for (i = 0; i < ndests; ++i)
    re_node_set_free (dests_node + i);

  if (dests_node_malloced)
    free (dests_alloc);

  return 1;
}