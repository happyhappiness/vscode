static unsigned int
internal_function
re_string_context_at (const re_string_t *input, int idx, int eflags)
{
  int c;
  if (BE (idx < 0, 0))
    /* In this case, we use the value stored in input->tip_context,
       since we can't know the character in input->mbs[-1] here.  */
    return input->tip_context;
  if (BE (idx == input->len, 0))
    return ((eflags & REG_NOTEOL) ? CONTEXT_ENDBUF
	    : CONTEXT_NEWLINE | CONTEXT_ENDBUF);
#ifdef RE_ENABLE_I18N
  if (input->mb_cur_max > 1)
    {
      wint_t wc;
      int wc_idx = idx;
      while(input->wcs[wc_idx] == WEOF)
	{
#ifdef DEBUG
	  /* It must not happen.  */
	  assert (wc_idx >= 0);
#endif
	  --wc_idx;
	  if (wc_idx < 0)
	    return input->tip_context;
	}
      wc = input->wcs[wc_idx];
      if (BE (input->word_ops_used != 0, 0) && IS_WIDE_WORD_CHAR (wc))
	return CONTEXT_WORD;
      return (IS_WIDE_NEWLINE (wc) && input->newline_anchor
	      ? CONTEXT_NEWLINE : 0);
    }
  else
#endif
    {
      c = re_string_byte_at (input, idx);
      if (bitset_contain (input->word_char, c))
	return CONTEXT_WORD;
      return IS_NEWLINE (c) && input->newline_anchor ? CONTEXT_NEWLINE : 0;
    }
}