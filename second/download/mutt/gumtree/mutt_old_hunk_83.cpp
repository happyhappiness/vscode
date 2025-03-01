    fflush (pgperr);
    rewind (pgperr);
    
    if (pgp_copy_checksig  (pgperr, s->fpout) >= 0)
      badsig = 0;

    safe_fclose (&pgperr);
    
    if ((rv = mutt_wait_filter (thepid)))
      badsig = -1;
    
     dprint (1, (debugfile, "pgp_verify_one: mutt_wait_filter returned %d.\n", rv));
  }
  
  state_attach_puts (_("[-- End of PGP output --]\n\n"), s);
  
  mutt_unlink (sigfile);
  mutt_unlink (pgperrfile);

  dprint (1, (debugfile, "pgp_verify_one: returning %d.\n", badsig));
  
  return badsig;
}

/*
 * This routine verifies a PGP/MIME signed body.
 */
void pgp_signed_handler (BODY *a, STATE *s)
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

  protocol = mutt_get_parameter ("protocol", a->parameter);
  a = a->parts;

  /* extract the protocol information */
  
  if (protocol)
  {
    char major[STRING];
    char *t;

    if ((protocol_minor = strchr(protocol, '/'))) protocol_minor++;
    
    strfcpy(major, protocol, sizeof(major));
    if((t = strchr(major, '/')))
      *t = '\0';
    
    protocol_major = mutt_check_mime_type (major);
  }

  /* consistency check */

  if (!(a && a->next && a->next->type == protocol_major && 
      !ascii_strcasecmp(a->next->subtype, protocol_minor)))
  {
    state_attach_puts(_("[-- Error: Inconsistent multipart/signed structure! --]\n\n"), s);
    mutt_body_handler (a, s);
    return;
  }

  if(!(protocol_major == TYPEAPPLICATION && !ascii_strcasecmp(protocol_minor, "pgp-signature"))
     && !(protocol_major == TYPEMULTIPART && !ascii_strcasecmp(protocol_minor, "mixed")))
  {
    state_mark_attach (s);
    state_printf(s, _("[-- Error: Unknown multipart/signed protocol %s! --]\n\n"), protocol);
    mutt_body_handler (a, s);
    return;
  }
  
  if (s->flags & M_DISPLAY)
  {
    
    pgp_fetch_signatures(&signatures, a->next, &sigcnt);
    
    if (sigcnt)
    {
      mutt_mktemp (tempfile);
      if (pgp_write_signed (a, s, tempfile) == 0)
      {
	for (i = 0; i < sigcnt; i++)
	{
	  if (signatures[i]->type == TYPEAPPLICATION 
	      && !ascii_strcasecmp(signatures[i]->subtype, "pgp-signature"))
	  {
	    if (pgp_verify_one (signatures[i], s, tempfile) != 0)
	      goodsig = 0;
	  }
	  else
	  {
	    state_mark_attach (s);
	    state_printf (s, _("[-- Warning: We can't verify %s/%s signatures. --]\n\n"),
			  TYPE(signatures[i]), signatures[i]->subtype);
	  }
	}
      }
      
      mutt_unlink (tempfile);

      b->goodsig = goodsig;
      
      dprint (2, (debugfile, "pgp_signed_handler: goodsig = %d\n", goodsig));
      
      /* Now display the signed body */
      state_attach_puts (_("[-- The following data is signed --]\n\n"), s);


      safe_free((void **) &signatures);
    }
    else
      state_attach_puts (_("[-- Warning: Can't find any signatures. --]\n\n"), s);
  }
  
  mutt_body_handler (a, s);
  
  if (s->flags & M_DISPLAY && sigcnt)
  {
    state_putc ('\n', s);
    state_attach_puts (_("[-- End of signed data --]\n"), s);
  }
}

/* Extract pgp public keys from messages or attachments */

void pgp_extract_keys_from_messages (HEADER *h)
{
  int i;
  char tempfname[_POSIX_PATH_MAX];
  FILE *fpout;

  if (h)
  {
    mutt_parse_mime_message (Context, h);
    if(h->pgp & PGPENCRYPT && !pgp_valid_passphrase ())
      return;
  }

  mutt_mktemp (tempfname);
  if (!(fpout = safe_fopen (tempfname, "w")))
  {
    mutt_perror (tempfname);
    return;
  }

