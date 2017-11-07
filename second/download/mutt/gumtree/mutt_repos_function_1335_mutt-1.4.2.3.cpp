void imap_unmunge_mbox_name (char *s)
{
  char *buf;

  imap_unquote_string(s);

  buf = safe_strdup (s);
  if (buf)
  {
    imap_utf7_decode (&buf);
    strncpy (s, buf, strlen (s));
  }
  
  safe_free ((void **) &buf);
}