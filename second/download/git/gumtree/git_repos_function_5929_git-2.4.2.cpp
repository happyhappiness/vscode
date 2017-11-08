static int
internal_function
re_string_skip_chars (re_string_t *pstr, int new_raw_idx, wint_t *last_wc)
{
  mbstate_t prev_st;
  int rawbuf_idx;
  size_t mbclen;
  wint_t wc = WEOF;

  /* Skip the characters which are not necessary to check.  */
  for (rawbuf_idx = pstr->raw_mbs_idx + pstr->valid_raw_len;
       rawbuf_idx < new_raw_idx;)
    {
      wchar_t wc2;
      int remain_len = pstr->len - rawbuf_idx;
      prev_st = pstr->cur_state;
      mbclen = __mbrtowc (&wc2, (const char *) pstr->raw_mbs + rawbuf_idx,
			  remain_len, &pstr->cur_state);
      if (BE (mbclen == (size_t) -2 || mbclen == (size_t) -1 || mbclen == 0, 0))
	{
	  /* We treat these cases as a single byte character.  */
	  if (mbclen == 0 || remain_len == 0)
	    wc = L'\0';
	  else
	    wc = *(unsigned char *) (pstr->raw_mbs + rawbuf_idx);
	  mbclen = 1;
	  pstr->cur_state = prev_st;
	}
      else
	wc = (wint_t) wc2;
      /* Then proceed the next character.  */
      rawbuf_idx += mbclen;
    }
  *last_wc = (wint_t) wc;
  return rawbuf_idx;
}