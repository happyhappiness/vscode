static crypt_key_t *get_candidates (LIST * hints, unsigned int app, int secret)
{
  crypt_key_t *db, *k, **kend;
  char *pattern;
  gpgme_error_t err;
  gpgme_ctx_t ctx;
  gpgme_key_t key;
  int idx;
  gpgme_user_id_t uid = NULL;

  pattern = list_to_pattern (hints);
  if (!pattern)
    return NULL;
  
  err = gpgme_new (&ctx);
  if (err) 
    {
      mutt_error (_("gpgme_new failed: %s"), gpgme_strerror (err));
      FREE (&pattern);
      return NULL;
    }

  db = NULL;
  kend = &db;
  
  if ((app & APPLICATION_PGP))
    {
      /* Its all a mess.  That old GPGME expects different things
         depending on the protocol.  For gpg we don' t need percent
         escaped pappert but simple strings passed in an array to the
         keylist_ext_start function. */
      LIST *l;
      size_t n;
      char **patarr;

      for(l=hints, n=0; l; l = l->next)
        {
          if (l->data && *l->data)
            n++;
        }
      if (!n)
        goto no_pgphints;

      patarr = safe_calloc (n+1, sizeof *patarr);
      for(l=hints, n=0; l; l = l->next)
        {
          if (l->data && *l->data)
            patarr[n++] = safe_strdup (l->data);
        }
      patarr[n] = NULL;
      err = gpgme_op_keylist_ext_start (ctx, (const char**)patarr, secret, 0);
      for (n=0; patarr[n]; n++)
        FREE (&patarr[n]);
      FREE (&patarr);
      if (err) 
        {
          mutt_error (_("gpgme_op_keylist_start failed: %s"),
                      gpgme_strerror (err));
          gpgme_release (ctx);
          FREE (&pattern);
          return NULL;
        }

      while (!(err = gpgme_op_keylist_next (ctx, &key)) )
        {
          unsigned int flags = 0;
	  
	  if (key_check_cap (key, KEY_CAP_CAN_ENCRYPT))
            flags |= KEYFLAG_CANENCRYPT;
	  if (key_check_cap (key, KEY_CAP_CAN_SIGN))
            flags |= KEYFLAG_CANSIGN;

          if (key->revoked)
            flags |= KEYFLAG_REVOKED;
          if (key->expired)
            flags |= KEYFLAG_EXPIRED;
          if (key->disabled)
            flags |= KEYFLAG_DISABLED;

#if 0 /* DISABLED code */
          if (!flags)
            {
	      /* Bug in gpg.  Capabilities are not listed for secret
		 keys.  Try to deduce them from the algorithm. */

	      switch (key->subkeys[0].pubkey_algo)
                {
                case GPGME_PK_RSA:
                  flags |= KEYFLAG_CANENCRYPT;
                  flags |= KEYFLAG_CANSIGN;
                  break;
                case GPGME_PK_ELG_E:
                  flags |= KEYFLAG_CANENCRYPT;
                  break;
                case GPGME_PK_DSA:
                  flags |= KEYFLAG_CANSIGN;
                  break;
                }
            }
#endif /* DISABLED code */

	  for (idx = 0, uid = key->uids; uid; idx++, uid = uid->next)
            {
              k = safe_calloc (1, sizeof *k);
              k->kobj = key;
              gpgme_key_ref (k->kobj);
              k->idx = idx;
              k->uid = uid->uid;
              k->flags = flags;
              if (uid->revoked)
                k->flags |= KEYFLAG_REVOKED;
              k->validity = uid->validity;
              *kend = k;
              kend = &k->next;
            }
          gpgme_key_unref (key);
        }
      if (gpg_err_code (err) != GPG_ERR_EOF)
        mutt_error (_("gpgme_op_keylist_next failed: %s"), gpgme_strerror (err));
      gpgme_op_keylist_end (ctx);
    no_pgphints:
      ;
    }

  if ((app & APPLICATION_SMIME))
    {
      /* and now look for x509 certificates */
      gpgme_set_protocol (ctx, GPGME_PROTOCOL_CMS);
      err = gpgme_op_keylist_start (ctx, pattern, 0);
      if (err) 
        {
          mutt_error (_("gpgme_op_keylist_start failed: %s"),
                      gpgme_strerror (err));
          gpgme_release (ctx);
          FREE (&pattern);
          return NULL;
        }

      while (!(err = gpgme_op_keylist_next (ctx, &key)) )
        {
          unsigned int flags = KEYFLAG_ISX509;

	  if (key_check_cap (key, KEY_CAP_CAN_ENCRYPT))
            flags |= KEYFLAG_CANENCRYPT;
	  if (key_check_cap (key, KEY_CAP_CAN_SIGN))
            flags |= KEYFLAG_CANSIGN;
          
	  for (idx = 0, uid = key->uids; uid; idx++, uid = uid->next)
            {
              k = safe_calloc (1, sizeof *k);
              k->kobj = key;
              gpgme_key_ref (k->kobj);
              k->idx = idx;
              k->uid = uid->uid;
              k->flags = flags;
              k->validity = uid->validity;
              *kend = k;
              kend = &k->next;
            }
          gpgme_key_unref (key);
        }
      if (gpg_err_code (err) != GPG_ERR_EOF)
        mutt_error (_("gpgme_op_keylist_next failed: %s"), gpgme_strerror (err));
      gpgme_op_keylist_end (ctx);
    }

  gpgme_release (ctx);
  FREE (&pattern);
  return db;
}