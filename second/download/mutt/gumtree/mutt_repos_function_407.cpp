static smime_key_t *smime_parse_key(char *buf)
{
  smime_key_t *key;
  char *pend, *p;
  int field = 0;

  key = safe_calloc (sizeof (smime_key_t), 1);

  for (p = buf; p; p = pend)
  {
    /* Some users manually maintain their .index file, and use a tab
     * as a delimiter, which the old parsing code (using fscanf)
     * happened to allow.  smime_keys.pl uses a space, so search for both.
     */
    if ((pend = strchr (p, ' ')) || (pend = strchr (p, '\t')) ||
        (pend = strchr (p, '\n')))
      *pend++ = 0;

    /* For backward compatibility, don't count consecutive delimiters
     * as an empty field.
     */
    if (!*p)
      continue;

    field++;

    switch (field)
    {
      case 1:                   /* mailbox */
        key->email = safe_strdup (p);
        break;
      case 2:                   /* hash */
        key->hash = safe_strdup (p);
        break;
      case 3:                   /* label */
        key->label = safe_strdup (p);
        break;
      case 4:                   /* issuer */
        key->issuer = safe_strdup (p);
        break;
      case 5:                   /* trust */
        key->trust = *p;
        break;
      case 6:                   /* purpose */
        while (*p)
        {
          switch (*p++)
          {
            case 'e':
              key->flags |= KEYFLAG_CANENCRYPT;
              break;

            case 's':
              key->flags |= KEYFLAG_CANSIGN;
              break;
          }
        }
        break;
    }
  }

  /* Old index files could be missing issuer, trust, and purpose,
   * but anything less than that is an error. */
  if (field < 3)
  {
    smime_free_key (&key);
    return NULL;
  }

  if (field < 4)
    key->issuer = safe_strdup ("?");

  if (field < 5)
    key->trust = 't';

  if (field < 6)
    key->flags = (KEYFLAG_CANENCRYPT | KEYFLAG_CANSIGN);

  return key;
}