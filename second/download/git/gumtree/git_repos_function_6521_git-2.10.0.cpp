static reg_errcode_t
internal_function
build_wcs_upper_buffer (re_string_t *pstr)
{
  mbstate_t prev_st;
  int src_idx, byte_idx, end_idx, remain_len;
  size_t mbclen;
#ifdef _LIBC
  char buf[MB_LEN_MAX];
  assert (MB_LEN_MAX >= pstr->mb_cur_max);
#else
  char buf[64];
#endif

  byte_idx = pstr->valid_len;
  end_idx = (pstr->bufs_len > pstr->len) ? pstr->len : pstr->bufs_len;

  /* The following optimization assumes that ASCII characters can be
     mapped to wide characters with a simple cast.  */
  if (! pstr->map_notascii && pstr->trans == NULL && !pstr->offsets_needed)
    {
      while (byte_idx < end_idx)
	{
	  wchar_t wc;

	  if (isascii (pstr->raw_mbs[pstr->raw_mbs_idx + byte_idx])
	      && mbsinit (&pstr->cur_state))
	    {
	      /* In case of a singlebyte character.  */
	      pstr->mbs[byte_idx]
		= toupper (pstr->raw_mbs[pstr->raw_mbs_idx + byte_idx]);
	      /* The next step uses the assumption that wchar_t is encoded
		 ASCII-safe: all ASCII values can be converted like this.  */
	      pstr->wcs[byte_idx] = (wchar_t) pstr->mbs[byte_idx];
	      ++byte_idx;
	      continue;
	    }

	  remain_len = end_idx - byte_idx;
	  prev_st = pstr->cur_state;
	  mbclen = __mbrtowc (&wc,
			      ((const char *) pstr->raw_mbs + pstr->raw_mbs_idx
			       + byte_idx), remain_len, &pstr->cur_state);
	  if (BE (mbclen + 2 > 2, 1))
	    {
	      wchar_t wcu = wc;
	      if (iswlower (wc))
		{
		  size_t mbcdlen;

		  wcu = towupper (wc);
		  mbcdlen = wcrtomb (buf, wcu, &prev_st);
		  if (BE (mbclen == mbcdlen, 1))
		    memcpy (pstr->mbs + byte_idx, buf, mbclen);
		  else
		    {
		      src_idx = byte_idx;
		      goto offsets_needed;
		    }
		}
	      else
		memcpy (pstr->mbs + byte_idx,
			pstr->raw_mbs + pstr->raw_mbs_idx + byte_idx, mbclen);
	      pstr->wcs[byte_idx++] = wcu;
	      /* Write paddings.  */
	      for (remain_len = byte_idx + mbclen - 1; byte_idx < remain_len ;)
		pstr->wcs[byte_idx++] = WEOF;
	    }
	  else if (mbclen == (size_t) -1 || mbclen == 0)
	    {
	      /* It is an invalid character or '\0'.  Just use the byte.  */
	      int ch = pstr->raw_mbs[pstr->raw_mbs_idx + byte_idx];
	      pstr->mbs[byte_idx] = ch;
	      /* And also cast it to wide char.  */
	      pstr->wcs[byte_idx++] = (wchar_t) ch;
	      if (BE (mbclen == (size_t) -1, 0))
		pstr->cur_state = prev_st;
	    }
	  else
	    {
	      /* The buffer doesn't have enough space, finish to build.  */
	      pstr->cur_state = prev_st;
	      break;
	    }
	}
      pstr->valid_len = byte_idx;
      pstr->valid_raw_len = byte_idx;
      return REG_NOERROR;
    }
  else
    for (src_idx = pstr->valid_raw_len; byte_idx < end_idx;)
      {
	wchar_t wc;
	const char *p;
      offsets_needed:
	remain_len = end_idx - byte_idx;
	prev_st = pstr->cur_state;
	if (BE (pstr->trans != NULL, 0))
	  {
	    int i, ch;

	    for (i = 0; i < pstr->mb_cur_max && i < remain_len; ++i)
	      {
		ch = pstr->raw_mbs [pstr->raw_mbs_idx + src_idx + i];
		buf[i] = pstr->trans[ch];
	      }
	    p = (const char *) buf;
	  }
	else
	  p = (const char *) pstr->raw_mbs + pstr->raw_mbs_idx + src_idx;
	mbclen = __mbrtowc (&wc, p, remain_len, &pstr->cur_state);
	if (BE (mbclen + 2 > 2, 1))
	  {
	    wchar_t wcu = wc;
	    if (iswlower (wc))
	      {
		size_t mbcdlen;

		wcu = towupper (wc);
		mbcdlen = wcrtomb ((char *) buf, wcu, &prev_st);
		if (BE (mbclen == mbcdlen, 1))
		  memcpy (pstr->mbs + byte_idx, buf, mbclen);
		else if (mbcdlen != (size_t) -1)
		  {
		    size_t i;

		    if (byte_idx + mbcdlen > pstr->bufs_len)
		      {
			pstr->cur_state = prev_st;
			break;
		      }

		    if (pstr->offsets == NULL)
		      {
			pstr->offsets = re_malloc (int, pstr->bufs_len);

			if (pstr->offsets == NULL)
			  return REG_ESPACE;
		      }
		    if (!pstr->offsets_needed)
		      {
			for (i = 0; i < (size_t) byte_idx; ++i)
			  pstr->offsets[i] = i;
			pstr->offsets_needed = 1;
		      }

		    memcpy (pstr->mbs + byte_idx, buf, mbcdlen);
		    pstr->wcs[byte_idx] = wcu;
		    pstr->offsets[byte_idx] = src_idx;
		    for (i = 1; i < mbcdlen; ++i)
		      {
			pstr->offset