static char *find_keys (ADDRESS *adrlist, unsigned int app, int oppenc_mode)
{
  LIST *crypt_hook_list, *crypt_hook = NULL;
  char *crypt_hook_val = NULL;
  const char *keyID = NULL;
  char *keylist = NULL, *t;
  size_t keylist_size = 0;
  size_t keylist_used = 0;
  ADDRESS *addr = NULL;
  ADDRESS *p, *q;
  crypt_key_t *k_info;
  const char *fqdn = mutt_fqdn (1);
  char buf[LONG_STRING];
  int forced_valid;
  int r;
  int key_selected;

#if 0
  *r_application = APPLICATION_PGP|APPLICATION_SMIME;
#endif

  for (p = adrlist; p ; p = p->next)
    {
      key_selected = 0;
      crypt_hook_list = crypt_hook = mutt_crypt_hook (p);
      do
      {
        q = p;
        forced_valid = 0;
        k_info = NULL;

        if (crypt_hook != NULL)
          {
            crypt_hook_val = crypt_hook->data;
            r = M_YES;
            if (! oppenc_mode && option(OPTCRYPTCONFIRMHOOK))
              {
                snprintf (buf, sizeof (buf), _("Use keyID = \"%s\" for %s?"),
                          crypt_hook_val, p->mailbox);
                r = mutt_yesorno (buf, M_YES);
              }
            if (r == M_YES)
              {
                if (crypt_is_numerical_keyid (crypt_hook_val))
                  {
                    keyID = crypt_hook_val;
                    if (strncmp (keyID, "0x", 2) == 0)
                      keyID += 2;
                    goto bypass_selection;                /* you don't see this. */
                  }

                /* check for e-mail address */
                if ((t = strchr (crypt_hook_val, '@')) && 
                    (addr = rfc822_parse_adrlist (NULL, crypt_hook_val)))
                  {
                    if (fqdn)
                      rfc822_qualify (addr, fqdn);
                    q = addr;
                  }
                else if (! oppenc_mode)
                  {
#if 0		  
                    k_info = crypt_getkeybystr (crypt_hook_val, KEYFLAG_CANENCRYPT, 
                                                *r_application, &forced_valid);
#else
                    k_info = crypt_getkeybystr (crypt_hook_val, KEYFLAG_CANENCRYPT, 
                                                app, &forced_valid);
#endif
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
            k_info = crypt_getkeybyaddr (q, KEYFLAG_CANENCRYPT,
                                        app, &forced_valid, oppenc_mode);
          }

        if ((k_info == NULL) && (! oppenc_mode))
          {
            snprintf (buf, sizeof (buf), _("Enter keyID for %s: "), q->mailbox);
            
            k_info = crypt_ask_for_key (buf, q->mailbox,
                                        KEYFLAG_CANENCRYPT,
#if 0
                                        *r_application,
#else
                                        app,
#endif
                                        &forced_valid);
          }

        if (k_info == NULL)
          {
            FREE (&keylist);
            rfc822_free_address (&addr);
            mutt_free_list (&crypt_hook_list);
            return NULL;
          }


        keyID = crypt_fpr_or_lkeyid (k_info);

#if 0
        if (k_info->flags & KEYFLAG_ISX509)
          *r_application &= ~APPLICATION_PGP;
        if (!(k_info->flags & KEYFLAG_ISX509))
          *r_application &= ~APPLICATION_SMIME;
#endif
        
    bypass_selection:
        keylist_size += mutt_strlen (keyID) + 4 + 1;
        safe_realloc (&keylist, keylist_size);
        sprintf (keylist + keylist_used, "%s0x%s%s", /* __SPRINTF_CHECKED__ */
                keylist_used ? " " : "",  keyID,
                forced_valid? "!":"");
        keylist_used = mutt_strlen (keylist);

        key_selected = 1;

        crypt_free_key (&k_info);
        rfc822_free_address (&addr);

        if (crypt_hook != NULL)
          crypt_hook = crypt_hook->next;

      } while (crypt_hook != NULL);

      mutt_free_list (&crypt_hook_list);
    }
  return (keylist);
}