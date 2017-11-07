void imap_utf7_decode (char **s)
{
  if (Charset)
  {
    char *t = utf7_to_utf8 (*s, strlen (*s), 0, 0);
    if (t && !mutt_convert_string (&t, "UTF-8", Charset, 0))
    {
      safe_free ((void **) s);
      *s = t;
    }
  }
}