static gpgme_key_t *create_recipient_set (const char *keylist,
                                          gpgme_protocol_t protocol)
{
  int err;
  const char *s;
  char buf[100];
  int i;
  gpgme_key_t *rset = NULL;
  unsigned int rset_n = 0;
  gpgme_key_t key = NULL;
  gpgme_ctx_t context = NULL;

  err = gpgme_new (&context);
  if (! err)
    err = gpgme_set_protocol (context, protocol);

  if (! err)
    {
      s = keylist;
      do {
	while (*s == ' ')
	  s++;
	for (i=0; *s && *s != ' ' && i < sizeof(buf)-1;)
	  buf[i++] = *s++;
	buf[i] = 0;
	if (*buf)
	  {
	    if (i>1 && buf[i-1] == '!') 
	      {
		/* The user selected to override the validity of that
		   key. */
		buf[i-1] = 0;
	    
		err = gpgme_get_key (context, buf, &key, 0);
		if (! err)
		  key->uids->validity = GPGME_VALIDITY_FULL;
		buf[i-1] = '!';
	      }
	    else
	      err = gpgme_get_key (context, buf, &key, 0);

            safe_realloc (&rset, sizeof (*rset) * (rset_n + 1));
	    if (! err)
              rset[rset_n++] = key;
	    else
	      {
		mutt_error (_("error adding recipient `%s': %s\n"),
			    buf, gpgme_strerror (err));
                rset[rset_n] = NULL;
                free_recipient_set (&rset);
		gpgme_release (context);
		return NULL;
	      }
	  }
      } while (*s);
    }

  /* NULL terminate.  */
  safe_realloc (&rset, sizeof (*rset) * (rset_n + 1));
  rset[rset_n++] = NULL;
  
  if (context)
    gpgme_release (context);

  return rset;
}