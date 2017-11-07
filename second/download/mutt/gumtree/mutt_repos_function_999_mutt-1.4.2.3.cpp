static pgp_key_t *parse_pub_line (char *buf, int *is_subkey, pgp_key_t *k)
{
  pgp_uid_t *uid = NULL;
  int field = 0, is_uid = 0;
  char *pend, *p;
  int trust = 0;
  int flags = 0;

  *is_subkey = 0;
  if (!*buf)
    return NULL;
  
  dprint (2, (debugfile, "parse_pub_line: buf = `%s'\n", buf));
  
  for (p = buf; p; p = pend)
  {
    if ((pend = strchr (p, ':')))
      *pend++ = 0;
    field++;
    if (field > 1 && !*p)
      continue;

    switch (field)
    {
      case 1:			/* record type */
      {
	dprint (2, (debugfile, "record type: %s\n", p));
	
	if (!mutt_strcmp (p, "pub"))
	  ;
	else if (!mutt_strcmp (p, "sub"))
	  *is_subkey = 1;
	else if (!mutt_strcmp (p, "sec"))
	  ;
	else if (!mutt_strcmp (p, "ssb"))
	  *is_subkey = 1;
	else if (!mutt_strcmp (p, "uid"))
	  is_uid = 1;
	else
	  return NULL;
	
	if (!(is_uid || (*is_subkey && option (OPTPGPIGNORESUB))))
	  k = safe_calloc (sizeof (pgp_key_t), 1);

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
	  k->flags |= flags;

	break;
      }
      case 3:			/* key length  */
      {
	
	dprint (2, (debugfile, "key len: %s\n", p));
	
	if (!(*is_subkey && option (OPTPGPIGNORESUB)))
	  k->keylen = atoi (p);	/* fixme: add validation checks */
	break;
      }
      case 4:			/* pubkey algo */
      {
	
	dprint (2, (debugfile, "pubkey algorithm: %s\n", p));
	
	if (!(*is_subkey && option (OPTPGPIGNORESUB)))
	{
	  k->numalg = atoi (p);
	  k->algorithm = pgp_pkalgbytype (atoi (p));
	}

	k->flags |= pgp_get_abilities (atoi (p));
	break;
      }
      case 5:			/* 16 hex digits with the long keyid. */
      {
	dprint (2, (debugfile, "key id: %s\n", p));
	
	if (!(*is_subkey && option (OPTPGPIGNORESUB)))
	  mutt_str_replace (&k->keyid, p);
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
	time.tm_year = atoi (tstr)-1900;
	tstr[7] = '\0';
	time.tm_mon = (atoi (tstr+5))-1;
	time.tm_mday = atoi (tstr+8);
	k->gen_time = mutt_mktime (&time, 0);
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
	if (!pend || !*p)
	  break;			/* empty field or no trailing colon */

	/* ignore user IDs on subkeys */
	if (!is_uid && (*is_subkey && option (OPTPGPIGNORESUB)))
	  break;
	
	dprint (2, (debugfile, "user ID: %s\n", p));
	
	uid = safe_calloc (sizeof (pgp_uid_t), 1);
	fix_uid (p);
	uid->addr = safe_strdup (p);
	uid->trust = trust;
	uid->flags |= flags;
	uid->parent = k;
	uid->next = k->address;
	k->address = uid;
	
	if (strstr (p, "ENCR"))
	  k->flags |= KEYFLAG_PREFER_ENCRYPTION;
	if (strstr (p, "SIGN"))
	  k->flags |= KEYFLAG_PREFER_SIGNING;

	break;
      }
      case 11:			/* signature class  */
        break;
      case 12:			/* key capabilities */
        break;
      default:
        break;
    }
  }
  return k;
}