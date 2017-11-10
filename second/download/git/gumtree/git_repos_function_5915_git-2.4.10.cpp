static reg_errcode_t
internal_function
# ifdef RE_ENABLE_I18N
build_collating_symbol (bitset_t sbcset, re_charset_t *mbcset,
			int *coll_sym_alloc, const unsigned char *name)
# else /* not RE_ENABLE_I18N */
build_collating_symbol (bitset_t sbcset, const unsigned char *name)
# endif /* not RE_ENABLE_I18N */
{
  size_t name_len = strlen ((const char *) name);
  if (BE (name_len != 1, 0))
    return REG_ECOLLATE;
  else
    {
      bitset_set (sbcset, name[0]);
      return REG_NOERROR;
    }
}