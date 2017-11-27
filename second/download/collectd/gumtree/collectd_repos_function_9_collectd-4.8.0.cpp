static error_t
argz_append (pargz, pargz_len, buf, buf_len)
     char **pargz;
     size_t *pargz_len;
     const char *buf;
     size_t buf_len;
{
  size_t argz_len;
  char  *argz;

  assert (pargz);
  assert (pargz_len);
  assert ((*pargz && *pargz_len) || (!*pargz && !*pargz_len));

  /* If nothing needs to be appended, no more work is required.  */
  if (buf_len == 0)
    return 0;

  /* Ensure there is enough room to append BUF_LEN.  */
  argz_len = *pargz_len + buf_len;
  argz = LT_DLREALLOC (char, *pargz, argz_len);
  if (!argz)
    return ENOMEM;

  /* Copy characters from BUF after terminating '\0' in ARGZ.  */
  memcpy (argz + *pargz_len, buf, buf_len);

  /* Assign new values.  */
  *pargz = argz;
  *pargz_len = argz_len;

  return 0;
}