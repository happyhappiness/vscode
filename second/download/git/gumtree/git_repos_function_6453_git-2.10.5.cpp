static int
internal_function
check_node_accept_bytes (const re_dfa_t *dfa, int node_idx,
			 const re_string_t *input, int str_idx)
{
  const re_token_t *node = dfa->nodes + node_idx;
  int char_len, elem_len;
  int i;
  wint_t wc;

  if (BE (node->type == OP_UTF8_PERIOD, 0))
    {
      unsigned char c = re_string_byte_at (input, str_idx), d;
      if (BE (c < 0xc2, 1))
	return 0;

      if (str_idx + 2 > input->len)
	return 0;

      d = re_string_byte_at (input, str_idx + 1);
      if (c < 0xe0)
	return (d < 0x80 || d > 0xbf) ? 0 : 2;
      else if (c < 0xf0)
	{
	  char_len = 3;
	  if (c == 0xe0 && d < 0xa0)
	    return 0;
	}
      else if (c < 0xf8)
	{
	  char_len = 4;
	  if (c == 0xf0 && d < 0x90)
	    return 0;
	}
      else if (c < 0xfc)
	{
	  char_len = 5;
	  if (c == 0xf8 && d < 0x88)
	    return 0;
	}
      else if (c < 0xfe)
	{
	  char_len = 6;
	  if (c == 0xfc && d < 0x84)
	    return 0;
	}
      else
	return 0;

      if (str_idx + char_len > input->len)
	return 0;

      for (i = 1; i < char_len; ++i)
	{
	  d = re_string_byte_at (input, str_idx + i);
	  if (d < 0x80 || d > 0xbf)
	    return 0;
	}
      return char_len;
    }

  char_len = re_string_char_size_at (input, str_idx);
  if (node->type == OP_PERIOD)
    {
      if (char_len <= 1)
	return 0;
      /* FIXME: I don't think this if is needed, as both '\n'
	 and '\0' are char_len == 1.  */
      /* '.' accepts any one character except the following two cases.  */
      if ((!(dfa->syntax & RE_DOT_NEWLINE) &&
	   re_string_byte_at (input, str_idx) == '\n') ||
	  ((dfa->syntax & RE_DOT_NOT_NULL) &&
	   re_string_byte_at (input, str_idx) == '\0'))
	return 0;
      return char_len;
    }

  elem_len = re_string_elem_size_at (input, str_idx);
  wc = __btowc(*(input->mbs+str_idx));
  if (((elem_len <= 1 && char_len <= 1) || char_len == 0) && (wc != WEOF && wc < SBC_MAX))
    return 0;

  if (node->type == COMPLEX_BRACKET)
    {
      const re_charset_t *cset = node->opr.mbcset;
# ifdef _LIBC
      const unsigned char *pin
	= ((const unsigned char *) re_string_get_buffer (input) + str_idx);
      int j;
      uint32_t nrules;
# endif /* _LIBC */
      int match_len = 0;
      wchar_t wc = ((cset->nranges || cset->nchar_classes || cset->nmbchars)
		    ? re_string_wchar_at (input, str_idx) : 0);

      /* match with multibyte character?  */
      for (i = 0; i < cset->nmbchars; ++i)
	if (wc == cset->mbchars[i])
	  {
	    match_len = char_len;
	    goto check_node_accept_bytes_match;
	  }
      /* match with character_class?  */
      for (i = 0; i < cset->nchar_classes; ++i)
	{
	  wctype_t wt = cset->char_classes[i];
	  if (__iswctype (wc, wt))
	    {
	      match_len = char_len;
	      goto check_node_accept_bytes_match;
	    }
	}

# ifdef _LIBC
      nrules = _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_NRULES);
      if (nrules != 0)
	{
	  unsigned int in_collseq = 0;
	  const int32_t *table, *indirect;
	  const unsigned char *weights, *extra;
	  const char *collseqwc;
	  /* This #include defines a local function!  */
#  include <locale/weight.h>

	  /* match with collating_symbol?  */
	  if (cset->ncoll_syms)
	    extra = (const unsigned char *)
	      _NL_CURRENT (LC_COLLATE, _NL_COLLATE_SYMB_EXTRAMB);
	  for (i = 0; i < cset->ncoll_syms; ++i)
	    {
	      const unsigned char *coll_sym = extra + cset->coll_syms[i];
	      /* Compare the length of input collating element and
		 the length of current collating element.  */
	      if (*coll_sym != elem_len)
		continue;
	      /* Compare each bytes.  */
	      for (j = 0; j < *coll_sym; j++)
		if (pin[j] != coll_sym[1 + j])
		  break;
	      if (j == *coll_sym)
		{
		  /* Match if every bytes is equal.  */
		  match_len = j;
		  goto check_node_accept_bytes_match;
		}
	    }

	  if (cset->nranges)
	    {
	      if (elem_len <= char_len)
		{
		  collseqwc = _NL_CURRENT (LC_COLLATE, _NL_COLLATE_COLLSEQWC);
		  in_collseq = __collseq_table_lookup (collseqwc, wc);
		}
	      else
		in_collseq = find_collation_sequence_value (pin, elem_len);
	    }
	  /* match with range expression?  */
	  for (i = 0; i < cset->nranges; ++i)
	    if (cset->range_starts[i] <= in_collseq
		&& in_collseq <= cset->range_ends[i])
	      {
		match_len = elem_len;
		goto check_node_accept_bytes_match;
	      }

	  /* match with equivalence_class?  */
	  if (cset->nequiv_classes)
	    {
	      const unsigned char *cp = pin;
	      table = (const int32_t *)
		_NL_CURRENT (LC_COLLATE, _NL_COLLATE_TABLEMB);
	      weights = (const unsigned char *)
		_NL_CURRENT (LC_COLLATE, _NL_COLLATE_WEIGHTMB);
	      extra = (const unsigned char *)
		_NL_CURRENT (LC_COLLATE, _NL_COLLATE_EXTRAMB);
	      indirect = (const int32_t *)
		_NL_CURRENT (LC_COLLATE, _NL_COLLATE_INDIRECTMB);
	      int32_t idx = findidx (&cp);
	      if (idx > 0)
		for (i = 0; i < cset->nequiv_classes; ++i)
		  {
		    int32_t equiv_class_idx = cset->equiv_classes[i];
		    size_t weight_len = weights[idx & 0xffffff];
		    if (weight_len == weights[equiv_class_idx & 0xffffff]
			&& (idx >> 24) == (equiv_class_idx >> 24))
		      {
			int cnt = 0;

			idx &= 0xffffff;
			equiv_class_idx &= 0xffffff;

			while (cnt <= weight_len
			       && (weights[equiv_class_idx + 1 + cnt]
				   == weights[idx + 1 + cnt]))
			  ++cnt;
			if (cnt > weight_len)
			  {
			    match_len = elem_len;
			    goto check_node_accept_bytes_match;
			  }
		      }
		  }
	    }
	}
      else
# endif /* _LIBC */
	{
	  /* match with range expression?  */
#if __GNUC__ >= 2
	  wchar_t cmp_buf[] = {L'\0', L'\0', wc, L'\0', L'\0', L'\0'};
#else
	  wchar_t cmp_buf[] = {L'\0', L'\0', L'\0', L'\0', L'\0', L'\0'};
	  cmp_buf[2] = wc;
#endif
	  for (i = 0; i < cset->nranges; ++i)
	    {
	      cmp_buf[0] = cset->range_starts[i];
	      cmp_buf[4] = cset->range_ends[i];
	      if (wcscoll (cmp_buf, cmp_buf + 2) <= 0
		  && wcscoll (cmp_buf + 2, cmp_buf + 4) <= 0)
		{
		  match_len = char_len;
		  goto check_node_accept_bytes_match;
		}
	    }
	}
    check_node_accept_bytes_match:
      if (!cset->non_match)
	return match_len;
      else
	{
	  if (match_len > 0)
	    return 0;
	  else
	    return (elem_len > char_len) ? elem_len : char_len;
	}
    }
  return 0;
}