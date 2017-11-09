static int
internal_function
search_cur_bkref_entry (const re_match_context_t *mctx, int str_idx)
{
  int left, right, mid, last;
  last = right = mctx->nbkref_ents;
  for (left = 0; left < right;)
    {
      mid = (left + right) / 2;
      if (mctx->bkref_ents[mid].str_idx < str_idx)
	left = mid + 1;
      else
	right = mid;
    }
  if (left < last && mctx->bkref_ents[left].str_idx == str_idx)
    return left;
  else
    return -1;
}