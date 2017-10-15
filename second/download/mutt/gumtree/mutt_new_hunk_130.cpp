      BEEP ();
    }
  /* not reached */
}

/* This routine attempts to find the keyids of the recipients of a
   message.  It returns NULL if any of the keys can not be found.
   If oppenc_mode is true, only keys that can be determined without
   prompting will be used.  */
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

char *pgp_gpgme_findkeys (ADDRESS *adrlist, int oppenc_mode)
{
  return find_keys (adrlist, APPLICATION_PGP, oppenc_mode);
}

char *smime_gpgme_findkeys (ADDRESS *adrlist, int oppenc_mode)
{
  return find_keys (adrlist, APPLICATION_SMIME, oppenc_mode);
}

#ifdef HAVE_GPGME_OP_EXPORT_KEYS
BODY *pgp_gpgme_make_key_attachment (char *tempf)
{
  crypt_key_t *key = NULL;
  gpgme_ctx_t context = NULL;
  gpgme_key_t export_keys[2];
  gpgme_data_t keydata = NULL;
  gpgme_error_t err;
  BODY *att = NULL;
  char buff[LONG_STRING];
  struct stat sb;

  unset_option (OPTPGPCHECKTRUST);

  key = crypt_ask_for_key (_("Please enter the key ID: "), NULL, 0,
                           APPLICATION_PGP, NULL);
  if (!key)
    goto bail;
  export_keys[0] = key->kobj;
  export_keys[1] = NULL;

  context = create_gpgme_context (0);
  gpgme_set_armor (context, 1);
  keydata = create_gpgme_data ();
  err = gpgme_op_export_keys (context, export_keys, 0, keydata);
  if (err != GPG_ERR_NO_ERROR)
  {
    mutt_error (_("Error exporting key: %s\n"), gpgme_strerror (err));
    mutt_sleep (1);
    goto bail;
  }

  tempf = data_object_to_tempfile (keydata, tempf, NULL);
  if (!tempf)
    goto bail;

  att = mutt_new_body ();
  /* tempf is a newly allocated string, so this is correct: */
  att->filename = tempf;
  att->unlink = 1;
  att->use_disp = 0;
  att->type = TYPEAPPLICATION;
  att->subtype = safe_strdup ("pgp-keys");
  snprintf (buff, sizeof (buff), _("PGP Key 0x%s."), crypt_keyid (key));
  att->description = safe_strdup (buff);
  mutt_update_encoding (att);

  stat (tempf, &sb);
  att->length = sb.st_size;

bail:
  crypt_free_key (&key);
  gpgme_data_release (keydata);
  gpgme_release (context);

  return att;
}
#endif

/*
 * Implementation of `init'.
 */

/* This function contains common code needed to be executed for both the pgp
