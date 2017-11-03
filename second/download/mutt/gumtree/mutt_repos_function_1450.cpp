static pgp_key_t parse_pub_line (char *buf, int *is_subkey, pgp_key_t k)
{
  pgp_uid_t *uid = NULL;
  int field = 0, is_uid = 0;
  int is_pub = 0;
  int is_fpr = 0;
  char *pend, *p;
  int trust = 0;
  int flags = 0;
  struct pgp_keyinfo tmp;

  *is_subkey = 0;
  if (!*buf)
    return NULL;

  /* if we're given a key, merge our parsing results, else
   * start with a fresh one to work with so that we don't
   * mess up the real key in case we find parsing errors. */
  if (k)
    memcpy (&tmp, k, sizeof (tmp));
  else
    memset (&tmp, 0, sizeof (tmp));

  dprint (2, (debugfile, "parse_pub_line: buf = `%s'\n", buf));

  for (p = buf; p; p = pend)
  {
    if ((pend = strchr (p, ':')))
      *pend++ = 0;
    field++;
    if (!*p && (field != 1) && (field != 10))
      continue;

    if (is_fpr && (field != 10))
      continue;

    switch (field)
    {
      case 1:			/* record type */
      {
	dprint (2, (debugfile, "record type: %s\n", p));

	if (!mutt_strcmp (p, "pub"))
	  is_pub = 1;
	else if (!mutt_strcmp (p, "sub"))
	  *is_subkey = 1;
	else if (!mutt_strcmp (p, "sec"))
	  ;
	else if (!mutt_strcmp (p, "ssb"))
	  *is_subkey = 1;
	else if (!mutt_strcmp (p, "uid"))
	  is_uid = 1;
	else if (!mutt_strcmp (p, "fpr"))
	  is_fpr = 1;
	else
	  return NULL;

	if (!(is_uid || is_fpr || (*is_subkey && option (OPTPGPIGNORESUB))))
	  memset (&tmp, 0, sizeof (tmp));

	break;
      }
      case 2:			/* trust info */
      {
	dprint (2, (debugfile, "trust info: %s\n", p));

	switch (*p)
	{				/* look only at the first letter */
	  case 'e':
	    flags |= KEYFLAG_EXPIRED;
	    break;
	  case 'r':
	    flags |= KEYFLAG_REVOKED;
	    break;
	  case 'd':
	    flags |= KEYFLAG_DISABLED;
	    break;
	  case 'n':
	    trust = 1;
	    break;
	  case 'm':
	    trust = 2;
	    break;
	  case 'f':
	    trust = 3;
	    break;
	  case 'u':
	    trust = 3;
	    break;
	}

        if (!is_uid && !(*is_subkey && option (OPTPGPIGNORESUB)))
	  tmp.flags |= flags;

	break;
      }
      case 3:			/* key length  */
      {
	dprint (2, (debugfile, "key len: %s\n", p));

	if (!(*is_subkey && option (OPTPGPIGNORESUB)) &&
	    mutt_atos (p, &tmp.keylen) < 0)
	  goto bail;
	break;
      }
      case 4:			/* pubkey algo */
      {
	dprint (2, (debugfile, "pubkey algorithm: %s\n", p));

	if (!(*is_subkey && option (OPTPGPIGNORESUB)))
	{
	  int x = 0;
	  if (mutt_atoi (p, &x) < 0)
	    goto bail;
	  tmp.numalg = x;
	  tmp.algorithm = pgp_pkalgbytype (x);
	}
	break;
      }
      case 5:			/* 16 hex digits with the long keyid. */
      {
	dprint (2, (debugfile, "key id: %s\n", p));

	if (!(*is_subkey && option (OPTPGPIGNORESUB)))
	  mutt_str_replace (&tmp.keyid, p);
	break;

      }
      case 6:			/* timestamp (1998-02-28) */
      {
	char tstr[11];
	struct tm time;

	dprint (2, (debugfile, "time stamp: %s\n", p));

	if (!p)
	  break;
	time.tm_sec = 0;
	time.tm_min = 0;
	time.tm_hour = 12;
	strncpy (tstr, p, 11);
	tstr[4] = '\0';
	tstr[7] = '\0';
	if (mutt_atoi (tstr, &time.tm_year) < 0)
	{
	  p = tstr;
	  goto bail;
	}
	time.tm_year -= 1900;
	if (mutt_atoi (tstr+5, &time.tm_mon) < 0)
	{
	  p = tstr+5;
	  goto bail;
	}
	time.tm_mon -= 1;
	if (mutt_atoi (tstr+8, &time.tm_mday) < 0)
	{
	  p = tstr+8;
	  goto bail;
	}
	tmp.gen_time = mutt_mktime (&time, 0);
        break;
      }
      case 7:			/* valid for n days */
        break;
      case 8:			/* Local id         */
        break;
      case 9:			/* ownertrust       */
        break;
      case 10:			/* name             */
      {
        /* Empty field or no trailing colon.
         * We allow an empty field for a pub record type because it is
         * possible for a primary uid record to have an empty User-ID
         * field.  Without any address records, it is not possible to
         * use the key in mutt.
         */
        if (!(pend && (*p || is_pub)))
	  break;

        if (is_fpr)
        {
          /* don't let a subkey fpr overwrite an existing primary key fpr */
          if (!tmp.fingerprint)
            tmp.fingerprint = safe_strdup (p);
          break;
        }

	/* ignore user IDs on subkeys */
	if (!is_uid && (*is_subkey && option (OPTPGPIGNORESUB)))
	  break;

	dprint (2, (debugfile, "user ID: %s\n", NONULL (p)));

	uid = safe_calloc (sizeof (pgp_uid_t), 1);
	fix_uid (p);
	uid->addr = safe_strdup (p);
	uid->trust = trust;
	uid->flags |= flags;
	uid->next = tmp.address;
	tmp.address = uid;

	if (strstr (p, "ENCR"))
	  tmp.flags |= KEYFLAG_PREFER_ENCRYPTION;
	if (strstr (p, "SIGN"))
	  tmp.flags |= KEYFLAG_PREFER_SIGNING;

	break;
      }
      case 11:			/* signature class  */
        break;
      case 12:			/* key capabilities */
	dprint (2, (debugfile, "capabilities info: %s\n", p));
	
	while(*p)
	  {
	    switch(*p++)
	      {
	      case 'D':
		flags |= KEYFLAG_DISABLED;
		break;

	      case 'e':
		flags |= KEYFLAG_CANENCRYPT;
		break;

	      case 's':
		flags |= KEYFLAG_CANSIGN;
		break;
	      }
	  }

        if (!is_uid && 
	    (!*is_subkey || !option (OPTPGPIGNORESUB)
	     || !((flags & KEYFLAG_DISABLED)
		  || (flags & KEYFLAG_REVOKED)
		  || (flags & KEYFLAG_EXPIRED))))
	  tmp.flags |= flags;

	break;
      
      default:
        break;
    }
  }

  /* merge temp key back into real key */
  if (!(is_uid || is_fpr || (*is_subkey && option (OPTPGPIGNORESUB))))
    k = safe_malloc (sizeof (*k));
  memcpy (k, &tmp, sizeof (*k));
  /* fixup parentship of uids after mering the temp key into
   * the real key */
  if (tmp.address)
  {
    for (uid = k->address; uid; uid = uid->next)
      uid->parent = k;
  }

  return k;

bail:
  dprint(5,(debugfile,"parse_pub_line: invalid number: '%s'\n", p));
  return NULL;
}