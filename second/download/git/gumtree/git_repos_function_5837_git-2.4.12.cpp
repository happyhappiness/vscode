static reg_errcode_t
internal_function
clean_state_log_if_needed (re_match_context_t *mctx, int next_state_log_idx)
{
  int top = mctx->state_log_top;

  if (next_state_log_idx >= mctx->input.bufs_len
      || (next_state_log_idx >= mctx->input.valid_len
	  && mctx->input.valid_len < mctx->input.len))
    {
      reg_errcode_t err;
      err = extend_buffers (mctx);
      if (BE (err != REG_NOERROR, 0))
	return err;
    }

  if (top < next_state_log_idx)
    {
      memset (mctx->state_log + top + 1, '\0',
	      sizeof (re_dfastate_t *) * (next_state_log_idx - top));
      mctx->state_log_top = next_state_log_idx;
    }
  return REG_NOERROR;
}