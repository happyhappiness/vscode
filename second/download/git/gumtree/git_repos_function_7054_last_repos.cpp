static reg_errcode_t
internal_function
re_string_realloc_buffers (re_string_t *pstr, int new_buf_len)
{
#ifdef RE_ENABLE_I18N
  if (pstr->mb_cur_max > 1)
    {
      wint_t *new_wcs;

      /* Avoid overflow in realloc.  */
      const size_t max_object_size = MAX (sizeof (wint_t), sizeof (int));
      if (BE (SIZE_MAX / max_object_size < new_buf_len, 0))
	return REG_ESPACE;

      new_wcs = re_realloc (pstr->wcs, wint_t, new_buf_len);
      if (BE (new_wcs == NULL, 0))
	return REG_ESPACE;
      pstr->wcs = new_wcs;
      if (pstr->offsets != NULL)
	{
	  int *new_offsets = re_realloc (pstr->offsets, int, new_buf_len);
	  if (BE (new_offsets == NULL, 0))
	    return REG_ESPACE;
	  pstr->offsets = new_offsets;
	}
    }
#endif /* RE_ENABLE_I18N  */
  if (pstr->mbs_allocated)
    {
      unsigned char *new_mbs = re_realloc (pstr->mbs, unsigned char,
					   new_buf_len);
      if (BE (new_mbs == NULL, 0))
	return REG_ESPACE;
      pstr->mbs = new_mbs;
    }
  pstr->bufs_len = new_buf_len;
  return REG_NOERROR;
}