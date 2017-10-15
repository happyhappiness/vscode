int pgp_gpgme_encrypted_handler (BODY *a, STATE *s)
{
  char tempfile[_POSIX_PATH_MAX];
  FILE *fpout;
  BODY *tattach;
  BODY *orig_body = a;
  int is_signed;
  int rc = 0;
  
  dprint (2, (debugfile, "Entering pgp_encrypted handler\n"));
  a = a->parts;
  if (!a || a->type != TYPEAPPLICATION || !a->subtype
      || ascii_strcasecmp ("pgp-encrypted", a->subtype) 
      || !a->next || a->next->type != TYPEAPPLICATION || !a->next->subtype
      || ascii_strcasecmp ("octet-stream", a->next->subtype) )
    {
      if (s->flags & M_DISPLAY)
        state_attach_puts (_("[-- Error: malformed PGP/MIME message! --]\n\n"),
                           s);
      return -1;
    }

  /* Move forward to the application/pgp-encrypted body. */
  a = a->next;

  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(fpout = safe_fopen (tempfile, "w+")))
    {
      if (s->flags & M_DISPLAY)
        state_attach_puts (_("[-- Error: could not create temporary file! "
                             "--]\n"), s);
      return -1;
    }

  tattach = decrypt_part (a, s, fpout, 0, &is_signed);
  if (tattach)
    {
      tattach->goodsig = is_signed > 0;

      if (s->flags & M_DISPLAY)
        state_attach_puts (is_signed?
          _("[-- The following data is PGP/MIME signed and encrypted --]\n\n"):
          _("[-- The following data is PGP/MIME encrypted --]\n\n"),
                           s);
      
      {
        FILE *savefp = s->fpin;
        s->fpin = fpout;
        rc = mutt_body_handler (tattach, s);
        s->fpin = savefp;
      }

      /* 
       * if a multipart/signed is the _only_ sub-part of a
       * multipart/encrypted, cache signature verification
       * status.
       */
      if (mutt_is_multipart_signed (tattach) && !tattach->next)
        orig_body->goodsig |= tattach->goodsig;
    
      if (s->flags & M_DISPLAY)
        {
          state_puts ("\n", s);
          state_attach_puts (is_signed?
             _("[-- End of PGP/MIME signed and encrypted data --]\n"):
             _("[-- End of PGP/MIME encrypted data --]\n"),
                             s);
        }

      mutt_free_body (&tattach);
    }
  
  safe_fclose (&fpout);
  mutt_unlink(tempfile);
  dprint (2, (debugfile, "Leaving pgp_encrypted handler\n"));

  return rc;
}