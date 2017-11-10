static int
internal_function
check_dst_limits_calc_pos (const re_match_context_t *mctx, int limit,
			   int subexp_idx, int from_node, int str_idx,
			   int bkref_idx)
{
  struct re_backref_cache_entry *lim = mctx->bkref_ents + limit;
  int boundaries;

  /* If we are outside the range of the subexpression, return -1 or 1.  */
  if (str_idx < lim->subexp_from)
    return -1;

  if (lim->subexp_to < str_idx)
    return 1;

  /* If we are within the subexpression, return 0.  */
  boundaries = (str_idx == lim->subexp_from);
  boundaries |= (str_idx == lim->subexp_to) << 1;
  if (boundaries == 0)
    return 0;

  /* Else, examine epsilon closure.  */
  return check_dst_limits_calc_pos_1 (mctx, boundaries, subexp_idx,
				      from_node, bkref_idx);
}