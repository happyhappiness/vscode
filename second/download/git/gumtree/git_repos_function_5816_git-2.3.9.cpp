static re_dfastate_t *
internal_function
transit_state (reg_errcode_t *err, re_match_context_t *mctx,
	       re_dfastate_t *state)
{
  re_dfastate_t **trtable;
  unsigned char ch;

#ifdef RE_ENABLE_I18N
  /* If the current state can accept multibyte.  */
  if (BE (state->accept_mb, 0))
    {
      *err = transit_state_mb (mctx, state);
      if (BE (*err != REG_NOERROR, 0))
	return NULL;
    }
#endif /* RE_ENABLE_I18N */

  /* Then decide the next state with the single byte.  */
#if 0
  if (0)
    /* don't use transition table  */
    return transit_state_sb (err, mctx, state);
#endif

  /* Use transition table  */
  ch = re_string_fetch_byte (&mctx->input);
  for (;;)
    {
      trtable = state->trtable;
      if (BE (trtable != NULL, 1))
	return trtable[ch];

      trtable = state->word_trtable;
      if (BE (trtable != NULL, 1))
	{
	  unsigned int context;
	  context
	    = re_string_context_at (&mctx->input,
				    re_string_cur_idx (&mctx->input) - 1,
				    mctx->eflags);
	  if (IS_WORD_CONTEXT (context))
	    return trtable[ch + SBC_MAX];
	  else
	    return trtable[ch];
	}

      if (!build_trtable (mctx->dfa, state))
	{
	  *err = REG_ESPACE;
	  return NULL;
	}

      /* Retry, we now have a transition table.  */
    }
}