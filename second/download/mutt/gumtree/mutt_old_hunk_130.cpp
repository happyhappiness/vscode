      BEEP ();
    }
  /* not reached */
}

/* This routine attempts to find the keyids of the recipients of a
   message.  It returns NULL if any of the keys can not be found.  */
static char *find_keys (ADDRESS *to, ADDRESS *cc, ADDRESS *bcc,
                        unsigned int app)
{
  char *keyID, *keylist = NULL, *t;
  size_t keylist_size = 0;
  size_t keylist_used = 0;
  ADDRESS *tmp = NULL, *addr = NULL;
  ADDRESS **last = &tmp;
  ADDRESS *p, *q;
  int i;
  crypt_key_t *k_info, *key;
  const char *fqdn = mutt_fqdn (1);

#if 0
  *r_application = APPLICATION_PGP|APPLICATION_SMIME;
#endif
  
  for (i = 0; i < 3; i++) 
    {
      switch (i)
        {
        case 0: p = to; break;
        case 1: p = cc; break;
        case 2: p = bcc; break;
        default: abort ();
        }
      
      *last = rfc822_cpy_adr (p, 0);
      while (*last)
        last = &((*last)->next);
    }
  
  if (fqdn)
    rfc822_qualify (tmp, fqdn);
  
  tmp = mutt_remove_duplicates (tmp);
  
  for (p = tmp; p ; p = p->next)
    {
      char buf[LONG_STRING];
      int forced_valid = 0;
      
      q = p;
      k_info = NULL;
      
      if ((keyID = mutt_crypt_hook (p)) != NULL)
        {
          int r;
          snprintf (buf, sizeof (buf), _("Use keyID = \"%s\" for %s?"),
                    keyID, p->mailbox);
          if ((r = mutt_yesorno (buf, M_YES)) == M_YES)
            {
              /* check for e-mail address */
              if ((t = strchr (keyID, '@')) && 
                  (addr = rfc822_parse_adrlist (NULL, keyID)))
                {
                  if (fqdn)
                    rfc822_qualify (addr, fqdn);
                  q = addr;
                }
              else
		{
#if 0		  
		  k_info = crypt_getkeybystr (keyID, KEYFLAG_CANENCRYPT, 
					      *r_application, &forced_valid);
#else
		  k_info = crypt_getkeybystr (keyID, KEYFLAG_CANENCRYPT, 
					      app, &forced_valid);
#endif
		}
            }
          else if (r == -1)
            {
              FREE (&keylist);
              rfc822_free_address (&tmp);
              rfc822_free_address (&addr);
              return NULL;
            }
        }

      if (k_info == NULL
          && (k_info = crypt_getkeybyaddr (q, KEYFLAG_CANENCRYPT,
                                           app, &forced_valid)) == NULL)
        {
          snprintf (buf, sizeof (buf), _("Enter keyID for %s: "), q->mailbox);
          
          if ((key = crypt_ask_for_key (buf, q->mailbox,
                                        KEYFLAG_CANENCRYPT,
#if 0
                                        *r_application,
#else
					app,
#endif
					&forced_valid)) == NULL)
            {
              FREE (&keylist);
              rfc822_free_address (&tmp);
              rfc822_free_address (&addr);
              return NULL;
            }
        }
      else
        key = k_info;

      {
        const char *s = crypt_fpr (key);

#if 0
        if (key->flags & KEYFLAG_ISX509)
          *r_application &= ~APPLICATION_PGP;
        if (!(key->flags & KEYFLAG_ISX509))
          *r_application &= ~APPLICATION_SMIME;
#endif
      
        keylist_size += mutt_strlen (s) + 4 + 1;
        safe_realloc (&keylist, keylist_size);
        sprintf (keylist + keylist_used, "%s0x%s%s", /* __SPRINTF_CHECKED__ */
                 keylist_used ? " " : "",  s,
                 forced_valid? "!":"");
      }
      keylist_used = mutt_strlen (keylist);
        
      crypt_free_key (&key);
      rfc822_free_address (&addr);
    }
  rfc822_free_address (&tmp);
  return (keylist);
}

char *pgp_gpgme_findkeys (ADDRESS *to, ADDRESS *cc, ADDRESS *bcc)
{
  return find_keys (to, cc, bcc, APPLICATION_PGP);
}

char *smime_gpgme_findkeys (ADDRESS *to, ADDRESS *cc, ADDRESS *bcc)
{
  return find_keys (to, cc, bcc, APPLICATION_SMIME);
}

/*
 * Implementation of `init'.
 */

/* This function contains common code needed to be executed for both the pgp
