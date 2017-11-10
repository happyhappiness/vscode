static re_dfastate_t *
internal_function
find_recover_state (reg_errcode_t *err, re_match_context_t *mctx)
{
  re_dfastate_t *cur_state;
  do
    {
      int max = mctx->state_log_top;
      int cur_str_idx = re_string_cur_idx (&mctx->input);

      do
	{
	  if (++cur_str_idx > max)
	    return NULL;
	  re_string_skip_bytes (&mctx->input, 1);
	}
      while (mctx->state_log[cur_str_idx] == NULL);

      cur_state = merge_state_with_log (err, mctx, NULL);
    }
  while (*err == REG_NOERROR && cur_state == NULL);
  return cur_state;
}