static const char *pgp_entry_fmt (char *dest,
				  size_t destlen,
				  size_t col,
                                  int cols,
				  char op,
				  const char *src,
				  const char *prefix,
				  const char *ifstring,
				  const char *elsestring,
				  unsigned long data,
				  format_flag flags)
{
  char fmt[16];
  pgp_entry_t *entry;
  pgp_uid_t *uid;
  pgp_key_t key, pkey;
  int kflags = 0;
  int optional = (flags & MUTT_FORMAT_OPTIONAL);

  entry = (pgp_entry_t *) data;
  uid   = entry->uid;
  key   = uid->parent;
  pkey  = pgp_principal_key (key);

  if (isupper ((unsigned char) op))
    key = pkey;

  kflags = key->flags | (pkey->flags & KEYFLAG_RESTRICTIONS)
    | uid->flags;

  switch (ascii_tolower (op))
  {
    case '[':

      {
	const char *cp;
	char buf2[SHORT_STRING], *p;
	int do_locales;
	struct tm *tm;
	size_t len;

	p = dest;

	cp = src;
	if (*cp == '!')
	{
	  do_locales = 0;
	  cp++;
	}
	else
	  do_locales = 1;

	len = destlen - 1;
	while (len > 0 && *cp != ']')
	{
	  if (*cp == '%')
	  {
	    cp++;
	    if (len >= 2)
	    {
	      *p++ = '%';
	      *p++ = *cp;
	      len -= 2;
	    }
	    else
	      break; /* not enough space */
	    cp++;
	  }
	  else
	  {
	    *p++ = *cp++;
	    len--;
	  }
	}
	*p = 0;

	if (do_locales && Locale)
	  setlocale (LC_TIME, Locale);

	tm = localtime (&key->gen_time);

	strftime (buf2, sizeof (buf2), dest, tm);

	if (do_locales)
	  setlocale (LC_TIME, "C");

	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, buf2);
	if (len > 0)
	  src = cp + 1;
      }
      break;
    case 'n':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (dest, destlen, fmt, entry->num);
      }
      break;
    case 'k':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, _pgp_keyid (key));
      }
      break;
    case 'u':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, NONULL (uid->addr));
      }
      break;
    case 'a':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, key->algorithm);
      }
      break;
    case 'l':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (dest, destlen, fmt, key->keylen);
      }
      break;
    case 'f':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sc", prefix);
	snprintf (dest, destlen, fmt, pgp_flags (kflags));
      }
      else if (!(kflags & (KEYFLAG_RESTRICTIONS)))
        optional = 0;
      break;
    case 'c':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, pgp_key_abilities (kflags));
      }
      else if (!(kflags & (KEYFLAG_ABILITIES)))
        optional = 0;
      break;
    case 't':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sc", prefix);
	snprintf (dest, destlen, fmt, trust_flags[uid->trust & 0x03]);
      }
      else if (!(uid->trust & 0x03))
        /* undefined trust */
        optional = 0;
      break;
    default:
      *dest = '\0';
  }

  if (optional)
    mutt_FormatString (dest, destlen, col, cols, ifstring, mutt_attach_fmt, data, 0);
  else if (flags & MUTT_FORMAT_OPTIONAL)
    mutt_FormatString (dest, destlen, col, cols, elsestring, mutt_attach_fmt, data, 0);
  return (src);
}