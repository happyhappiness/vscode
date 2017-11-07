void imap_utf7_encode (char **s)
{
  if (Charset)
  {
    char *t = safe_strdup (*s);
    if (!mutt_convert_string (&t, Charset, "UTF-8", 0))
      utf8_to_utf7 (t, strlen (t), s, 0);
    safe_free ((void **) &t);
  }
}