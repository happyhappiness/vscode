int mutt_signed_handler (BODY *a, STATE *s)
{
  char tempfile[_POSIX_PATH_MAX];
  char *protocol;
  int protocol_major = TYPEOTHER;
  char *protocol_minor = NULL;
  
  BODY *b = a;
  BODY **signatures = NULL;
  int sigcnt = 0;
  int i;
  short goodsig = 1;
  int rc = 0;

  if (!WithCrypto)
    return -1;

  protocol = mutt_get_parameter ("protocol", a->parameter);
  a = a->parts;

  /* extract the protocol information */
  
  if (protocol)
  {
    char major[STRING];
    char *t;

    if ((protocol_minor = strchr (protocol, '/'))) protocol_minor++;
    
    strfcpy (major, protocol, sizeof(major));
    if((t = strchr(major, '/')))
      *t = '\0';
    
    protocol_major = mutt_check_mime_type (major);
  }

  /* consistency check */

  if (!(a && a->next && a->next->type == protocol_major && 
      !mutt_strcasecmp (a->next->subtype, protocol_minor)))
  {
    state_attach_puts (_("[-- Error: "
                         "Inconsistent multipart/signed structure! --]\n\n"),
                       s);
    return mutt_body_handler (a, s);
  }

  
  if ((WithCrypto & APPLICATION_PGP)
      && protocol_major == TYPEAPPLICATION
      && !ascii_strcasecmp (protocol_minor, "pgp-signature"))
    ;
  else if ((WithCrypto & APPLICATION_SMIME)
           && protocol_major == TYPEAPPLICATION
	   && !(ascii_strcasecmp (protocol_minor, "x-pkcs7-signature")
	       && ascii_strcasecmp (protocol_minor, "pkcs7-signature")))
    ;
  else if (protocol_major == TYPEMULTIPART
	   && !ascii_strcasecmp (protocol_minor, "mixed"))
    ;
  else
  {
    state_printf (s, _("[-- Error: "
                       "Unknown multipart/signed protocol %s! --]\n\n"),
                  protocol);
    return mutt_body_handler (a, s);
  }
  
  if (s->flags & M_DISPLAY)
  {
    
    crypt_fetch_signatures (&signatures, a->next, &sigcnt);
    
    if (sigcnt)
    {
      mutt_mktemp (tempfile, sizeof (tempfile));
      if (crypt_write_signed (a, s, tempfile) == 0)
      {
	for (i = 0; i < sigcnt; i++)
	{
	  if ((WithCrypto & APPLICATION_PGP)
              && signatures[i]->type == TYPEAPPLICATION 
	      && !ascii_strcasecmp (signatures[i]->subtype, "pgp-signature"))
	  {
	    if (crypt_pgp_verify_one (signatures[i], s, tempfile) != 0)
	      goodsig = 0;
	    
	    continue;
	  }

	  if ((WithCrypto & APPLICATION_SMIME)
              && signatures[i]->type == TYPEAPPLICATION 
	      && (!ascii_strcasecmp(signatures[i]->subtype, "x-pkcs7-signature")
		  || !ascii_strcasecmp(signatures[i]->subtype, "pkcs7-signature")))
	  {
	    if (crypt_smime_verify_one (signatures[i], s, tempfile) != 0)
	      goodsig = 0;
	    
	    continue;
	  }

	  state_printf (s, _("[-- Warning: "
                             "We can't verify %s/%s signatures. --]\n\n"),
			  TYPE(signatures[i]), signatures[i]->subtype);
	}
      }
      
      mutt_unlink (tempfile);

      b->goodsig = goodsig;
      b->badsig  = !goodsig;
      
      /* Now display the signed body */
      state_attach_puts (_("[-- The following data is signed --]\n\n"), s);


      FREE (&signatures);
    }
    else
      state_attach_puts (_("[-- Warning: Can't find any signatures. --]\n\n"), s);
  }
  
  rc = mutt_body_handler (a, s);
  
  if (s->flags & M_DISPLAY && sigcnt)
    state_attach_puts (_("\n[-- End of signed data --]\n"), s);
  
  return rc;
}