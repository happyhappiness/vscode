char *pgp_findKeys (ADDRESS *adrlist, int oppenc_mode)
{
  LIST *crypt_hook_list, *crypt_hook = NULL;
  char *keyID, *keylist = NULL;
  size_t keylist_size = 0;
  size_t keylist_used = 0;
  ADDRESS *addr = NULL;
  ADDRESS *p, *q;
  pgp_key_t k_info = NULL;
  char buf[LONG_STRING];
  int r;
  int key_selected;

  const char *fqdn = mutt_fqdn (1);

  for (p = adrlist; p ; p = p->next)
  {
    key_selected = 0;
    crypt_hook_list = crypt_hook = mutt_crypt_hook (p);
    do
    {
      q = p;
      k_info = NULL;

      if (crypt_hook != NULL)
      {
        keyID = crypt_hook->data;
        r = M_YES;
        if (! oppenc_mode && option(OPTCRYPTCONFIRMHOOK))
        {
          snprintf (buf, sizeof (buf), _("Use keyID = \"%s\" for %s?"), keyID, p->mailbox);
          r = mutt_yesorno (buf, M_YES);
        }
        if (r == M_YES)
        {
          if (crypt_is_numerical_keyid (keyID))
          {
            if (strncmp (keyID, "0x", 2) == 0)
              keyID += 2;
            goto bypass_selection;		/* you don't see this. */
          }

          /* check for e-mail address */
          if (strchr (keyID, '@') &&
              (addr = rfc822_parse_adrlist (NULL, keyID)))
          {
            if (fqdn) rfc822_qualify (addr, fqdn);
            q = addr;
          }
          else if (! oppenc_mode)
          {
            k_info = pgp_getkeybystr (keyID, KEYFLAG_CANENCRYPT, PGP_PUBRING);
          }
        }
        else if (r == M_NO)
        {
          if (key_selected || (crypt_hook->next != NULL))
          {
            crypt_hook = crypt_hook->next;
            continue;
          }
        }
        else if (r == -1)
        {
          FREE (&keylist);
          rfc822_free_address (&addr);
          mutt_free_list (&crypt_hook_list);
          return NULL;
        }
      }

      if (k_info == NULL)
      {
        pgp_invoke_getkeys (q);
        k_info = pgp_getkeybyaddr (q, KEYFLAG_CANENCRYPT, PGP_PUBRING, oppenc_mode);
      }

      if ((k_info == NULL) && (! oppenc_mode))
      {
        snprintf (buf, sizeof (buf), _("Enter keyID for %s: "), q->mailbox);
        k_info = pgp_ask_for_key (buf, q->mailbox,
                              KEYFLAG_CANENCRYPT, PGP_PUBRING);
      }

      if (k_info == NULL)
      {
        FREE (&keylist);
        rfc822_free_address (&addr);
        mutt_free_list (&crypt_hook_list);
        return NULL;
      }

      keyID = pgp_fpr_or_lkeyid (k_info);

    bypass_selection:
      keylist_size += mutt_strlen (keyID) + 4;
      safe_realloc (&keylist, keylist_size);
      sprintf (keylist + keylist_used, "%s0x%s", keylist_used ? " " : "",	/* __SPRINTF_CHECKED__ */
              keyID);
      keylist_used = mutt_strlen (keylist);

      key_selected = 1;

      pgp_free_key (&k_info);
      rfc822_free_address (&addr);

      if (crypt_hook != NULL)
        crypt_hook = crypt_hook->next;

    } while (crypt_hook != NULL);

    mutt_free_list (&crypt_hook_list);
  }
  return (keylist);
}