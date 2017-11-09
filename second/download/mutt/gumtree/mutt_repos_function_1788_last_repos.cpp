static void pretty_var (char *dst, size_t len, const char *option, const char *val)
{
  char *p;

  if (!len)
    return;

  strfcpy (dst, option, len);
  len--; /* save room for \0 */
  p = dst + mutt_strlen (dst);

  if (p - dst < len)
    *p++ = '=';
  if (p - dst < len)
    *p++ = '"';
  p += escape_string (p, len - (p - dst) + 1, val);	/* \0 terminate it */
  if (p - dst < len)
    *p++ = '"';
  *p = 0;
}