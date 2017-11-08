static reg_errcode_t
internal_function
# ifdef RE_ENABLE_I18N
build_range_exp (bitset_t sbcset, re_charset_t *mbcset, int *range_alloc,
		 bracket_elem_t *start_elem, bracket_elem_t *end_elem)
# else /* not RE_ENABLE_I18N */
build_range_exp (bitset_t sbcset, bracket_elem_t *start_elem,
		 bracket_elem_t *end_elem)
# endif /* not RE_ENABLE_I18N */
{
  unsigned int start_ch, end_ch;
  /* Equivalence Classes and Character Classes can't be a range start/end.  */
  if (BE (start_elem->type == EQUIV_CLASS || start_elem->type == CHAR_CLASS
	  || end_elem->type == EQUIV_CLASS || end_elem->type == CHAR_CLASS,
	  0))
    return REG_ERANGE;

  /* We can handle no multi character collating elements without libc
     support.  */
  if (BE ((start_elem->type == COLL_SYM
	   && strlen ((char *) start_elem->opr.name) > 1)
	  || (end_elem->type == COLL_SYM
	      && strlen ((char *) end_elem->opr.name) > 1), 0))
    return REG_ECOLLATE;

# ifdef RE_ENABLE_I18N
  {
    wchar_t wc;
    wint_t start_wc;
    wint_t end_wc;
    wchar_t cmp_buf[6] = {L'\0', L'\0', L'\0', L'\0', L'\0', L'\0'};

    start_ch = ((start_elem->type == SB_CHAR) ? start_elem->opr.ch
		: ((start_elem->type == COLL_SYM) ? start_elem->opr.name[0]
		   : 0));
    end_ch = ((end_elem->type == SB_CHAR) ? end_elem->opr.ch
	      : ((end_elem->type == COLL_SYM) ? end_elem->opr.name[0]
		 : 0));
#ifdef GAWK
    /*
     * Fedora Core 2, maybe others, have broken `btowc' that returns -1
     * for any value > 127. Sigh. Note that `start_ch' and `end_ch' are
     * unsigned, so we don't have sign extension problems.
     */
    start_wc = ((start_elem->type == SB_CHAR || start_elem->type == COLL_SYM)
		? start_ch : start_elem->opr.wch);
    end_wc = ((end_elem->type == SB_CHAR || end_elem->type == COLL_SYM)
	      ? end_ch : end_elem->opr.wch);
#else
    start_wc = ((start_elem->type == SB_CHAR || start_elem->type == COLL_SYM)
		? __btowc (start_ch) : start_elem->opr.wch);
    end_wc = ((end_elem->type == SB_CHAR || end_elem->type == COLL_SYM)
	      ? __btowc (end_ch) : end_elem->opr.wch);
#endif
    if (start_wc == WEOF || end_wc == WEOF)
      return REG_ECOLLATE;
    cmp_buf[0] = start_wc;
    cmp_buf[4] = end_wc;
    if (wcscoll (cmp_buf, cmp_buf + 4) > 0)
      return REG_ERANGE;

    /* Got valid collation sequence values, add them as a new entry.
       However, for !_LIBC we have no collation elements: if the
       character set is single byte, the single byte character set
       that we build below suffices.  parse_bracket_exp passes
       no MBCSET if dfa->mb_cur_max == 1.  */
    if (mbcset)
      {
	/* Check the space of the arrays.  */
	if (BE (*range_alloc == mbcset->nranges, 0))
	  {
	    /* There is not enough space, need realloc.  */
	    wchar_t *new_array_start, *new_array_end;
	    int new_nranges;

	    /* +1 in case of mbcset->nranges is 0.  */
	    new_nranges = 2 * mbcset->nranges + 1;
	    /* Use realloc since mbcset->range_starts and mbcset->range_ends
	       are NULL if *range_alloc == 0.  */
	    new_array_start = re_realloc (mbcset->range_starts, wchar_t,
					  new_nranges);
	    new_array_end = re_realloc (mbcset->range_ends, wchar_t,
					new_nranges);

	    if (BE (new_array_start == NULL || new_array_end == NULL, 0))
	      return REG_ESPACE;

	    mbcset->range_starts = new_array_start;
	    mbcset->range_ends = new_array_end;
	    *range_alloc = new_nranges;
	  }

	mbcset->range_starts[mbcset->nranges] = start_wc;
	mbcset->range_ends[mbcset->nranges++] = end_wc;
      }

    /* Build the table for single byte characters.  */
    for (wc = 0; wc < SBC_MAX; ++wc)
      {
	cmp_buf[2] = wc;
	if (wcscoll (cmp_buf, cmp_buf + 2) <= 0
	    && wcscoll (cmp_buf + 2, cmp_buf + 4) <= 0)
	  bitset_set (sbcset, wc);
      }
  }
# else /* not RE_ENABLE_I18N */
  {
    unsigned int ch;
    start_ch = ((start_elem->type == SB_CHAR ) ? start_elem->opr.ch
		: ((start_elem->type == COLL_SYM) ? start_elem->opr.name[0]
		   : 0));
    end_ch = ((end_elem->type == SB_CHAR ) ? end_elem->opr.ch
	      : ((end_elem->type == COLL_SYM) ? end_elem->opr.name[0]
		 : 0));
    if (start_ch > end_ch)
      return REG_ERANGE;
    /* Build the table for single byte characters.  */
    for (ch = 0; ch < SBC_MAX; ++ch)
      if (start_ch <= ch  && ch <= end_ch)
	bitset_set (sbcset, ch);
  }
# endif /* not RE_ENABLE_I18N */
  return REG_NOERROR;
}