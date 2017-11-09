char *smime_findKeys (ADDRESS *adrlist, int oppenc_mode)
{
  smime_key_t *key = NULL;
  char *keyID, *keylist = NULL;
  size_t keylist_size = 0;
  size_t keylist_used = 0;
  ADDRESS *p, *q;

  for (p = adrlist; p ; p = p->next)
  {
    char buf[LONG_STRING];

    q = p;

    key = smime_get_key_by_addr (q->mailbox, KEYFLAG_CANENCRYPT, 1, !oppenc_mode);
    if ((key == NULL) && (! oppenc_mode))
    {
      snprintf(buf, sizeof(buf),
	       _("Enter keyID for %s: "),
	       q->mailbox);
      key = smime_ask_for_key (buf, KEYFLAG_CANENCRYPT, 1);
    }
    if (!key)
    {
      if (! oppenc_mode)
        mutt_message (_("No (valid) certificate found for %s."), q->mailbox);
      FREE (&keylist);
      return NULL;
    }

    keyID = key->hash;
    keylist_size += mutt_strlen (keyID) + 2;
    safe_realloc (&keylist, keylist_size);
    sprintf (keylist + keylist_used, "%s%s", keylist_used ? " " : "", keyID);	/* __SPRINTF_CHECKED__ */
    keylist_used = mutt_strlen (keylist);

    smime_free_key (&key);
  }
  return (keylist);
}