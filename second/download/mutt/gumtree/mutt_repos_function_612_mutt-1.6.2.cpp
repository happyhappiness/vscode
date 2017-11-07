static void recode_buf (char *buf, size_t buflen)
{
  char *s;

  if (!ConfigCharset || !*ConfigCharset || !Charset)
    return;
  s = safe_strdup (buf);
  if (!s)
    return;
  if (mutt_convert_string (&s, Charset, ConfigCharset, 0) == 0)
    strfcpy (buf, s, buflen);
  FREE(&s);
}