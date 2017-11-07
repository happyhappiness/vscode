int mutt_signed_handler (BODY *a, STATE *s)
{
  char tempfile[_POSIX_PATH_MAX];
  int signed_type;
  int inconsistent = 0;
  
  BODY *b = a;
  BODY **signatures = NULL;
  int sigcnt = 0;
  int i;
  short goodsig = 1;
  int rc = 0;

  if (!WithCrypto)
    return -1;

  a = a->parts;
  signed_type = mutt_is_multipart_signed (b);
  if (!signed_type)
  {
    /* A null protocol value is already checked for in mutt_body_handler() */
    state_printf (s, _("[-- Error: "
                       "Unknown multipart/signed protocol %s! --]\n\n"),
                  mutt_get_parameter ("protocol", b->parameter));
    return mutt_body_handler (a, s);
  }

  if (!(a && a->next))
    inconsistent = 1;
  else
  {
    switch (signed_type)
    {
      case SIGN:
        if (a->next->type != TYPEMULTIPART ||
            ascii_strcasecmp (a->next->subtype, "mixed"))
          inconsistent = 1;
        break;
      case PGPSIGN:
        if (a->next->type != TYPEAPPLICATION ||
            ascii_strcasecmp (a->next->subtype, "pgp-signature"))
          inconsistent = 1;
        break;
      case SMIMESIGN:
        if (a->next->type != TYPEAPPLICATION ||
            (ascii_strcasecmp (a->next->subtype, "x-pkcs7-signature") &&
             ascii_strcasecmp (a->next->subtype, "pkcs7-signature")))
          inconsistent = 1;
        break;
      default:
        inconsistent = 1;
    }
  }
  if (inconsistent)
  {
    state_attach_puts (_("[-- Error: "
                         "Inconsistent multipart/signed structure! --]\n\n"),
                       s);
    return mutt_body_handler (a, s);
  }

  if (s->flags & MUTT_DISPLAY)
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
  
  if (s->flags & MUTT_DISPLAY && sigcnt)
    state_attach_puts (_("\n[-- End of signed data --]\n"), s);
  
  return rc;
}