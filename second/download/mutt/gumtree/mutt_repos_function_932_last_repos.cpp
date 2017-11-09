void mutt_canonical_charset (char *dest, size_t dlen, const char *name)
{
  size_t i;
  char *p, *ext;
  char in[LONG_STRING], scratch[LONG_STRING];

  strfcpy (in, name, sizeof (in));
  if ((ext = strchr (in, '/')))
    *ext++ = 0;

  if (!ascii_strcasecmp (in, "utf-8") || !ascii_strcasecmp (in, "utf8"))
  {
    strfcpy (dest, "utf-8", dlen);
    goto out;
  }

  /* catch some common iso-8859-something misspellings */
  if (!ascii_strncasecmp (in, "8859", 4) && in[4] != '-')
    snprintf (scratch, sizeof (scratch), "iso-8859-%s", in +4);
  else if (!ascii_strncasecmp (in, "8859-", 5))
    snprintf (scratch, sizeof (scratch), "iso-8859-%s", in + 5);
  else if (!ascii_strncasecmp (in, "iso8859", 7) && in[7] != '-')
    snprintf (scratch, sizeof (scratch), "iso_8859-%s", in + 7);
  else if (!ascii_strncasecmp (in, "iso8859-", 8))
    snprintf (scratch, sizeof (scratch), "iso_8859-%s", in + 8);
  else
    strfcpy (scratch, in, sizeof (scratch));

  for (i = 0; PreferredMIMENames[i].key; i++)
    if (!ascii_strcasecmp (scratch, PreferredMIMENames[i].key) ||
	!mutt_strcasecmp (scratch, PreferredMIMENames[i].key))
    {
      strfcpy (dest, PreferredMIMENames[i].pref, dlen);
      goto out;
    }

  strfcpy (dest, scratch, dlen);

  /* for cosmetics' sake, transform to lowercase. */
  for (p = dest; *p; p++)
    *p = ascii_tolower (*p);

out:
  if (ext && *ext)
  {
    safe_strcat (dest, dlen, "/");
    safe_strcat (dest, dlen, ext);
  }
}