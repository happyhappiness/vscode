void imap_munge_mbox_name (char *dest, size_t dlen, const char *src)
{
  char *buf;

  buf = safe_strdup (src);
  imap_utf7_encode (&buf);

  imap_quote_string (dest, dlen, buf);

  safe_free ((void **) &buf);
}