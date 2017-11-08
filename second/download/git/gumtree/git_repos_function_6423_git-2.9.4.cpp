static reg_errcode_t
internal_function
re_string_allocate (re_string_t *pstr, const char *str, int len, int init_len,
		    RE_TRANSLATE_TYPE trans, int icase, const re_dfa_t *dfa)
{
  reg_errcode_t ret;
  int init_buf_len;

  /* Ensure at least one character fits into the buffers.  */
  if (init_len < dfa->mb_cur_max)
    init_len = dfa->mb_cur_max;
  init_buf_len = (len + 1 < init_len) ? len + 1: init_len;
  re_string_construct_common (str, len, pstr, trans, icase, dfa);

  ret = re_string_realloc_buffers (pstr, init_buf_len);
  if (BE (ret != REG_NOERROR, 0))
    return ret;

  pstr->word_char = dfa->word_char;
  pstr->word_ops_used = dfa->word_ops_used;
  pstr->mbs = pstr->mbs_allocated ? pstr->mbs : (unsigned char *) str;
  pstr->valid_len = (pstr->mbs_allocated || dfa->mb_cur_max > 1) ? 0 : len;
  pstr->valid_raw_len = pstr->valid_len;
  return REG_NOERROR;
}