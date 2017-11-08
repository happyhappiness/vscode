static reg_errcode_t
internal_function
get_subexp_sub (re_match_context_t *mctx, const re_sub_match_top_t *sub_top,
		re_sub_match_last_t *sub_last, int bkref_node, int bkref_str)
{
  reg_errcode_t err;
  int to_idx;
  /* Can the subexpression arrive the back reference?  */
  err = check_arrival (mctx, &sub_last->path, sub_last->node,
		       sub_last->str_idx, bkref_node, bkref_str,
		       OP_OPEN_SUBEXP);
  if (err != REG_NOERROR)
    return err;
  err = match_ctx_add_entry (mctx, bkref_node, bkref_str, sub_top->str_idx,
			     sub_last->str_idx);
  if (BE (err != REG_NOERROR, 0))
    return err;
  to_idx = bkref_str + sub_last->str_idx - sub_top->str_idx;
  return clean_state_log_if_needed (mctx, to_idx);
}