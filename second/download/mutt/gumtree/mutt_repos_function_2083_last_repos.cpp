void imap_utf_encode (IMAP_DATA *idata, char **s)
{
  if (Charset)
  {
    char *t = safe_strdup (*s);
    if (t && !mutt_convert_string (&t, Charset, "utf-8", 0))
    {
      FREE (s);		/* __FREE_CHECKED__ */
      if (idata->unicode)
        *s = safe_strdup (t);
      else
        *s = utf8_to_utf7 (t, strlen (t), NULL, 0);
    }
    FREE (&t);
  }
}