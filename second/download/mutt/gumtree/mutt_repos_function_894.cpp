void mutt_set_langinfo_charset (void)
{
  char buff[LONG_STRING];
  char buff2[LONG_STRING];
  
  strfcpy (buff, nl_langinfo (CODESET), sizeof (buff));
  mutt_canonical_charset (buff2, sizeof (buff2), buff);
  
  /* finally, set $charset */
  if (!(Charset = safe_strdup (buff2)))
    Charset = safe_strdup ("iso-8859-1");
}