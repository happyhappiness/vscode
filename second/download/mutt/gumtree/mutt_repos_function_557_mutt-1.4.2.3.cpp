void mutt_canonical_charset (char *dest, size_t dlen, const char *name)
{
  size_t i;
  char *p;
  char scratch[LONG_STRING];

  /* catch some common iso-8859-something misspellings */
  if (!ascii_strncasecmp (name, "8859", 4) && name[4] != '-')
    snprintf (scratch, sizeof (scratch), "iso-8859-%s", name +4);
  else if (!ascii_strncasecmp (name, "8859-", 5))
    snprintf (scratch, sizeof (scratch), "iso-8859-%s", name + 5);
  else if (!ascii_strncasecmp (name, "iso8859", 7) && name[7] != '-')
    snprintf (scratch, sizeof (scratch), "iso_8859-%s", name + 7);
  else if (!ascii_strncasecmp (name, "iso8859-", 8))
    snprintf (scratch, sizeof (scratch), "iso_8859-%s", name + 8);
  else
    strfcpy (scratch, NONULL(name), sizeof (scratch));

  for (i = 0; PreferredMIMENames[i].key; i++)
    if (!ascii_strcasecmp (scratch, PreferredMIMENames[i].key) ||
	!mutt_strcasecmp (scratch, PreferredMIMENames[i].key))
    {
      strfcpy (dest, PreferredMIMENames[i].pref, dlen);
      return;
    }

  strfcpy (dest, scratch, dlen);

  /* for cosmetics' sake, transform to lowercase. */
  for (p = dest; *p; p++)
    *p = ascii_tolower (*p);
}