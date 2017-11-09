static reg_errcode_t
internal_function
re_string_reconstruct (re_string_t *pstr, int idx, int eflags)
{
  int offset = idx - pstr->raw_mbs_idx;
  if (BE (offset < 0, 0))
    {
      /* Reset buffer.  */
#ifdef RE_ENABLE_I18N
      if (pstr->mb_cur_max > 1)
	memset (&pstr->cur_state, '\0', sizeof (mbstate_t));
#endif /* RE_ENABLE_I18N */
      pstr->len = pstr->raw_len;
      pstr->stop = pstr->raw_stop;
      pstr->valid_len = 0;
      pstr->raw_mbs_idx = 0;
      pstr->valid_raw_len = 0;
      pstr->offsets_needed = 0;
      pstr->tip_context = ((eflags & REG_NOTBOL) ? CONTEXT_BEGBUF
			   : CONTEXT_NEWLINE | CONTEXT_BEGBUF);
      if (!pstr->mbs_allocated)
	pstr->mbs = (unsigned char *) pstr->raw_mbs;
      offset = idx;
    }

  if (BE (offset != 0, 1))
    {
      /* Should the already checked characters be kept?  */
      if (BE (offset < pstr->valid_raw_len, 1))
	{
	  /* Yes, move them to the front of the buffer.  */
#ifdef RE_ENABLE_I18N
	  if (BE (pstr->offsets_needed, 0))
	    {
	      int low = 0, high = pstr->valid_len, mid;
	      do
		{
		  mid = (high + low) / 2;
		  if (pstr->offsets[mid] > offset)
		    high = mid;
		  else if (pstr->offsets[mid] < offset)
		    low = mid + 1;
		  else
		    break;
		}
	      while (low < high);
	      if (pstr->offsets[mid] < offset)
		++mid;
	      pstr->tip_context = re_string_context_at (pstr, mid - 1,
							eflags);
	      /* This can be quite complicated, so handle specially
		 only the common and easy case where the character with
		 different length representation of lower and upper
		 case is present at or after offset.  */
	      if (pstr->valid_len > offset
		  && mid == offset && pstr->offsets[mid] == offset)
		{
		  memmove (pstr->wcs, pstr->wcs + offset,
			   (pstr->valid_len - offset) * sizeof (wint_t));
		  memmove (pstr->mbs, pstr->mbs + offset, pstr->valid_len - offset);
		  pstr->valid_len -= offset;
		  pstr->valid_raw_len -= offset;
		  for (low = 0; low < pstr->valid_len; low++)
		    pstr->offsets[low] = pstr->offsets[low + offset] - offset;
		}
	      else
		{
		  /* Otherwise, just find out how long the partial multibyte
		     character at offset is and fill it with WEOF/255.  */
		  pstr->len = pstr->raw_len - idx + offset;
		  pstr->stop = pstr->raw_stop - idx + offset;
		  pstr->offsets_needed = 0;
		  while (mid > 0 && pstr->offsets[mid - 1] == offset)
		    --mid;
		  while (mid < pstr->valid_len)
		    if (pstr->wcs[mid] != WEOF)
		      break;
		    else
		      ++mid;
		  if (mid == pstr->valid_len)
		    pstr->valid_len = 0;
		  else
		    {
		      pstr->valid_len = pstr->offsets[mid] - offset;
		      if (pstr->valid_len)
			{
			  for (low = 0; low < pstr->valid_len; ++low)
			    pstr->wcs[low] = WEOF;
			  memset (pstr->mbs, 255, pstr->valid_len);
			}
		    }
		  pstr->valid_raw_len = pstr->valid_len;
		}
	    }
	  else
#endif
	    {
	      pstr->tip_context = re_string_context_at (pstr, offset - 1,
							eflags);
#ifdef RE_ENABLE_I18N
	      if (pstr->mb_cur_max > 1)
		memmove (pstr->wcs, pstr->wcs + offset,
			 (pstr->valid_len - offset) * sizeof (wint_t));
#endif /* RE_ENABLE_I18N */
	      if (BE (pstr->mbs_allocated, 0))
		memmove (pstr->mbs, pstr->mbs + offset,
			 pstr->valid_len - offset);
	      pstr->valid_len -= offset;
	      pstr->valid_raw_len -= offset;
#if DEBUG
	      assert (pstr->valid_len > 0);
#endif
	    }
	}
      else
	{
#ifdef RE_ENABLE_I18N
	  /* No, skip all characters until IDX.  */
	  int prev_valid_len = pstr->valid_len;

	  if (BE (pstr->offsets_needed, 0))
	    {
	      pstr->len = pstr->raw_len - idx + offset;
	      pstr->stop = pstr->raw_stop - idx + offset;
	      pstr->offsets_needed = 0;
	    }
#endif
	  pstr->valid_len = 0;
#ifdef RE_ENABLE_I18N
	  if (pstr->mb_cur_max > 1)
	    {
	      int wcs_idx;
	      wint_t wc = WEOF;

	      if (pstr->is_utf8)
		{
		  const unsigned char *raw, *p, *end;

		  /* Special case UTF-8.  Multi-byte chars start with any
		     byte other than 0x80 - 0xbf.  */
		  raw = pstr->raw_mbs + pstr->raw_mbs_idx;
		  end = raw + (offset - pstr->mb_cur_max);
		  if (end < pstr->raw_mbs)
		    end = pstr->raw_mbs;
		  p = raw + offset - 1;
#ifdef _LIBC
		  /* We know the wchar_t encoding is UCS4, so for the simple
		     case, ASCII characters, skip the conversion step.  */
		  if (isascii (*p) && BE (pstr->trans == NULL, 1))
		    {
		      memset (&pstr->cur_state, '\0', sizeof (mbstate_t));
		      /* pstr->valid_len = 0; */
		      wc = (wchar_t) *p;
		    }
		  else
#endif
		    for (; p >= end; --p)
		      if ((*p & 0xc0) != 0x80)
			{
			  mbstate_t cur_state;
			  wchar_t wc2;
			  int mlen = raw + pstr->len - p;
			  unsigned char buf[6];
			  size_t mbclen;

			  if (BE (pstr->trans != NULL, 0))
			    {
			      int i = mlen < 6 ? mlen : 6;
			      while (--i >= 0)
				buf[i] = pstr->trans[p[i]];
			    }
			  /* XXX Don't use mbrtowc, we know which conversion
			     to use (UTF-8 -> UCS4).  */
			  memset (&cur_state, 0, sizeof (cur_state));
			  mbclen = __mbrtowc (&wc2, (const char *) p, mlen,
					      &cur_state);
			  if (raw + offset - p <= mbclen
			      && mbclen < (size_t) -2)
			    {
			      memset (&pstr->cur_state, '\0',
				      sizeof (mbstate_t));
			      pstr->valid_len = mbclen - (raw + offset - p);
			      wc = wc2;
			    }
			  break;
			}
		}

	      if (wc == WEOF)
		pstr->valid_len = re_string_skip_chars (pstr, idx, &wc) - idx;
	      if (wc == WEOF)
		pstr->tip_context
		  = re_string_context_at (pstr, prev_valid_len - 1, eflags);
	      else
		pstr->tip_context = ((BE (pstr->word_ops_used != 0, 0)
				      && IS_WIDE_WORD_CHAR (wc))
				     ? CONTEXT_WORD
				     : ((IS_WIDE_NEWLINE (wc)
					 && pstr->newline_anchor)
					? CONTEXT_NEWLINE : 0));
	      if (BE (pstr->valid_len, 0))
		{
		  for (wcs_idx = 0; wcs_idx < pstr->valid_len; ++wcs_idx)
		    pstr->wcs[wcs_idx] = WEOF;
		  if (pstr->mbs_allocated)
		    memset (pstr->mbs, 255, pstr->valid_len);
		}
	      pstr->valid_raw_len = pstr->valid_len;
	    }
	  else
#endif /* RE_ENABLE_I18N */
	    {
	      int c = pstr->raw_mbs[pstr->raw_mbs_idx + offset - 1];
	      pstr->valid_raw_len = 0;
	      if (pstr->trans)
		c = pstr->trans[c];
	      pstr->tip_context = (bitset_contain (pstr->word_char, c)
				   ? CONTEXT_WORD
				   : ((IS_NEWLINE (c) && pstr->newline_anchor)
				      ? CONTEXT_NEWLINE : 0));
	    }
	}
      if (!BE (pstr->mbs_allocated, 0))
	pstr->mbs += offset;
    }
  pstr->raw_mbs_idx = idx;
  pstr->len -= offset;
  pstr->stop -= offset;

  /* Then build the buffers.  */
#ifdef RE_ENABLE_I18N
  if (pstr->mb_cur_max > 1)
    {
      if (pstr->icase)
	{
	  reg_errcode_t ret = build_wcs_upper_buffer (pstr);
	  if (BE (ret != REG_NOERROR, 0))
	    return ret;
	}
      else
	build_wcs_buffer (pstr);
    }
  else
#endif /* RE_ENABLE_I18N */
    if (BE (pstr->mbs_allocated, 0))
      {
	if (pstr->icase)
	  build_upper_buffer (pstr);
	else if (pstr->trans != NULL)
	  re_string_translate_buffer (pstr);
      }
    else
      pstr->valid_len = pstr->len;

  pstr->cur_idx = 0;
  return REG_NOERROR;
}