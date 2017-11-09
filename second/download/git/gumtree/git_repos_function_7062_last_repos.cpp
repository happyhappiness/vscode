static void
internal_function
re_string_destruct (re_string_t *pstr)
{
#ifdef RE_ENABLE_I18N
  re_free (pstr->wcs);
  re_free (pstr->offsets);
#endif /* RE_ENABLE_I18N  */
  if (pstr->mbs_allocated)
    re_free (pstr->mbs);
}