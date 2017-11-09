static reg_errcode_t
internal_function
extend_buffers (re_match_context_t *mctx)
{
  reg_errcode_t ret;
  re_string_t *pstr = &mctx->input;

  /* Avoid overflow.  */
  if (BE (INT_MAX / 2 / sizeof (re_dfastate_t *) <= pstr->bufs_len, 0))
    return REG_ESPACE;

  /* Double the lengths of the buffers.  */
  ret = re_string_realloc_buffers (pstr, pstr->bufs_len * 2);
  if (BE (ret != REG_NOERROR, 0))
    return ret;

  if (mctx->state_log != NULL)
    {
      /* And double the length of state_log.  */
      /* XXX We have no indication of the size of this buffer.  If this
	 allocation fail we have no indication that the state_log array
	 does not have the right size.  */
      re_dfastate_t **new_array = re_realloc (mctx->state_log, re_dfastate_t *,
					      pstr->bufs_len + 1);
      if (BE (new_array == NULL, 0))
	return REG_ESPACE;
      mctx->state_log = new_array;
    }

  /* Then reconstruct the buffers.  */
  if (pstr->icase)
    {
#ifdef RE_ENABLE_I18N
      if (pstr->mb_cur_max > 1)
	{
	  ret = build_wcs_upper_buffer (pstr);
	  if (BE (ret != REG_NOERROR, 0))
	    return ret;
	}
      else
#endif /* RE_ENABLE_I18N  */
	build_upper_buffer (pstr);
    }
  else
    {
#ifdef RE_ENABLE_I18N
      if (pstr->mb_cur_max > 1)
	build_wcs_buffer (pstr);
      else
#endif /* RE_ENABLE_I18N  */
	{
	  if (pstr->trans != NULL)
	    re_string_translate_buffer (pstr);
	}
    }
  return REG_NOERROR;
}