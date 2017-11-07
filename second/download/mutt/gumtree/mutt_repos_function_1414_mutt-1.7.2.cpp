void mutt_encode_path (char *dest, size_t dlen, const char *src)
{
  char *p = safe_strdup (src);
  int rc = mutt_convert_string (&p, Charset, "utf-8", 0);
  /* `src' may be NULL, such as when called from the pop3 driver. */
  strfcpy (dest, (rc == 0) ? NONULL(p) : NONULL(src), dlen);
  FREE (&p);
}