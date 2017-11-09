static const char *crypt_entry_fmt (char *dest,
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
  crypt_entry_t *entry;
  crypt_key_t *key;
  int kflags = 0;
  int optional = (flags & MUTT_FORMAT_OPTIONAL);
  const char *s = NULL;
  unsigned long val;

  entry = (crypt_entry_t *) data;
  key   = entry->key;

/*    if (isupper ((unsigned char) op)) */
/*      key = pkey; */

  kflags = (key->flags /*| (pkey->flags & KEYFLAG_RESTRICTIONS)
                         | uid->flags*/);
  
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

        {
	  time_t tt = 0;

	  if (key->kobj->subkeys && (key->kobj->subkeys->timestamp > 0))
	    tt = key->kobj->subkeys->timestamp;

          tm = localtime (&tt);
        }

        if (!do_locales)
          setlocale (LC_TIME, "C");
        strftime (buf2, sizeof (buf2), dest, tm);
        if (!do_locales)
          setlocale (LC_TIME, "");

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
        /* fixme: we need a way to distinguish between main and subkeys.
           Store the idx in entry? */
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, crypt_keyid (key));
      }
      break;
    case 'u':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, key->uid);
      }
      break;
    case 'a':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%s.3s", prefix);
	if (key->kobj->subkeys)
	  s = gpgme_pubkey_algo_name (key->kobj->subkeys->pubkey_algo);
	else
          s = "?";
	snprintf (dest, destlen, fmt, s);
      }
      break;
    case 'l':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%slu", prefix);
	if (key->kobj->subkeys)
	  val = key->kobj->subkeys->length;
	else
	  val = 0;
	snprintf (dest, destlen, fmt, val);
      }
      break;
    case 'f':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sc", prefix);
	snprintf (dest, destlen, fmt, crypt_flags (kflags));
      }
      else if (!(kflags & (KEYFLAG_RESTRICTIONS)))
        optional = 0;
      break;
    case 'c':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	snprintf (dest, destlen, fmt, crypt_key_abilities (kflags));
      }
      else if (!(kflags & (KEYFLAG_ABILITIES)))
        optional = 0;
      break;
    case 't':
      if ((kflags & KEYFLAG_ISX509))
        s = "x";
      else
	{
          switch (key->validity)
            {
            case GPGME_VALIDITY_UNDEFINED:
              s = "q";
              break;
            case GPGME_VALIDITY_NEVER:
              s = "n";
              break;
            case GPGME_VALIDITY_MARGINAL:
              s = "m";
              break;
            case GPGME_VALIDITY_FULL:
              s = "f";
              break;
            case GPGME_VALIDITY_ULTIMATE:
              s = "u";
              break;
            case GPGME_VALIDITY_UNKNOWN:
            default:
              s = "?";
              break;
            }
	}
      snprintf (fmt, sizeof (fmt), "%%%sc", prefix);
      snprintf (dest, destlen, fmt, s? *s: 'B');
      break;
    case 'p':
      snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
      snprintf (dest, destlen, fmt,
                gpgme_get_protocol_name (key->kobj->protocol));
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