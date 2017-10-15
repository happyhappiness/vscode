    {
      state_puts ("\n", s);
      state_attach_puts (_("[-- End of PGP/MIME encrypted data --]\n"), s);
    }

    mutt_free_body (&tattach);
    /* clear 'Invoking...' message, since there's no error */
    mutt_message _("PGP message successfully decrypted.");
  }
  else
  {
    mutt_error _("Could not decrypt PGP message");
    /* void the passphrase, even if it's not necessarily the problem */
    pgp_void_passphrase ();
    rc = -1;
  }

  safe_fclose (&fpout);
  mutt_unlink(tempfile);

  return rc;
}

/* ----------------------------------------------------------------------------
 * Routines for sending PGP/MIME messages.
 */


BODY *pgp_sign_message (BODY *a)
{
  BODY *t;
  char buffer[LONG_STRING];
  char sigfile[_POSIX_PATH_MAX], signedfile[_POSIX_PATH_MAX];
  FILE *pgpin, *pgpout, *pgperr, *fp, *sfp;
  int err = 0;
  int empty = 1;
  pid_t thepid;
  
  convert_to_7bit (a); /* Signed data _must_ be in 7-bit format. */

  mutt_mktemp (sigfile, sizeof (sigfile));
  if ((fp = safe_fopen (sigfile, "w")) == NULL)
  {
    return (NULL);
  }

  mutt_mktemp (signedfile, sizeof (signedfile));
  if ((sfp = safe_fopen(signedfile, "w")) == NULL)
  {
    mutt_perror(signedfile);
    safe_fclose (&fp);
    unlink(sigfile);
    return NULL;
  }
  
  mutt_write_mime_header (a, sfp);
  fputc ('\n', sfp);
  mutt_write_mime_body (a, sfp);
  safe_fclose (&sfp);
  
  if ((thepid = pgp_invoke_sign (&pgpin, &pgpout, &pgperr,
				 -1, -1, -1, signedfile)) == -1)
  {
    mutt_perror _("Can't open PGP subprocess!");
    safe_fclose (&fp);
    unlink(sigfile);
    unlink(signedfile);
    return NULL;
  }
  
  if (!pgp_use_gpg_agent())
     fputs(PgpPass, pgpin);
  fputc('\n', pgpin);
  safe_fclose (&pgpin);
  
  /*
   * Read back the PGP signature.  Also, change MESSAGE=>SIGNATURE as
   * recommended for future releases of PGP.
   */
  while (fgets (buffer, sizeof (buffer) - 1, pgpout) != NULL)
