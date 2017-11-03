void imap_utf_decode (IMAP_DATA *idata, char **s)
{
  char *t;

  if (Charset)
  {
    if (idata->unicode)
      t = safe_strdup (*s);
    else
      t = utf7_to_utf8 (*s, strlen (*s), 0, 0);

    if (t && !mutt_convert_string (&t, "utf-8", Charset, 0))
    {
      FREE (s);		/* __FREE_CHECKED__ */
      *s = t;
    }
    else
      FREE (&t);
  }
}