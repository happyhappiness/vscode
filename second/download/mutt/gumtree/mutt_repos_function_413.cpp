void _smime_getkeys (char *mailbox)
{
  smime_key_t *key = NULL;
  char *k = NULL;
  char buf[STRING];

  key = smime_get_key_by_addr (mailbox, KEYFLAG_CANENCRYPT, 0, 1);

  if (!key)
  {
    snprintf(buf, sizeof(buf), _("Enter keyID for %s: "),
	     mailbox);
    key = smime_ask_for_key (buf, KEYFLAG_CANENCRYPT, 0);
  }

  if (key)
  {
    k = key->hash;

    /* the key used last time. */
    if (*SmimeKeyToUse && 
        !mutt_strcasecmp (k, SmimeKeyToUse + mutt_strlen (SmimeKeys)+1))
    {
      smime_free_key (&key);
      return;
    }
    else smime_void_passphrase ();

    snprintf (SmimeKeyToUse, sizeof (SmimeKeyToUse), "%s/%s", 
	      NONULL(SmimeKeys), k);
    
    snprintf (SmimeCertToUse, sizeof (SmimeCertToUse), "%s/%s",
	      NONULL(SmimeCertificates), k);

    if (mutt_strcasecmp (k, SmimeDefaultKey))
      smime_void_passphrase ();

    smime_free_key (&key);
    return;
  }

  if (*SmimeKeyToUse)
  {
    if (!mutt_strcasecmp (SmimeDefaultKey, 
                          SmimeKeyToUse + mutt_strlen (SmimeKeys)+1))
      return;

    smime_void_passphrase ();
  }

  snprintf (SmimeKeyToUse, sizeof (SmimeKeyToUse), "%s/%s", 
	    NONULL (SmimeKeys), NONULL (SmimeDefaultKey));
  
  snprintf (SmimeCertToUse, sizeof (SmimeCertToUse), "%s/%s",
	    NONULL (SmimeCertificates), NONULL (SmimeDefaultKey));
}