int smime_gpgme_application_handler (BODY *a, STATE *s)
{
  char tempfile[_POSIX_PATH_MAX];
  FILE *fpout;
  BODY *tattach;
  int is_signed;
  int rc = 0;

  dprint (2, (debugfile, "Entering smime_encrypted handler\n"));
  
  a->warnsig = 0;
  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(fpout = safe_fopen (tempfile, "w+")))
    {
      if (s->flags & MUTT_DISPLAY)
        state_attach_puts (_("[-- Error: could not create temporary file! "
                             "--]\n"), s);
      return -1;
    }

  tattach = decrypt_part (a, s, fpout, 1, &is_signed);
  if (tattach)
    {
      tattach->goodsig = is_signed > 0;

      if (s->flags & MUTT_DISPLAY)
        state_attach_puts (is_signed?
          _("[-- The following data is S/MIME signed --]\n\n"):
          _("[-- The following data is S/MIME encrypted --]\n\n"),
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
        {
          if (!(a->goodsig = tattach->goodsig))
            a->warnsig = tattach->warnsig;
        }
      else if (tattach->goodsig)
        {
          a->goodsig = 1;
          a->warnsig = tattach->warnsig;
        }

      if (s->flags & MUTT_DISPLAY)
        {
          state_puts ("\n", s);
          state_attach_puts (is_signed?
             _("[-- End of S/MIME signed data --]\n"):
             _("[-- End of S/MIME encrypted data --]\n"),
                             s);
        }

      mutt_free_body (&tattach);
    }
  
  safe_fclose (&fpout);
  mutt_unlink(tempfile);
  dprint (2, (debugfile, "Leaving smime_encrypted handler\n"));
  
  return rc;
}