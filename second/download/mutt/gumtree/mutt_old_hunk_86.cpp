    {
      state_puts ("\n", s);
      state_attach_puts (_("[-- End of PGP/MIME encrypted data --]\n"), s);
    }

    mutt_free_body (&tattach);
  }

  fclose (fpout);
  mutt_unlink(tempfile);
}

/* ----------------------------------------------------------------------------
 * Routines for sending PGP/MIME messages.
 */

static void convert_to_7bit (BODY *a)
{
  while (a)
  {
    if (a->type == TYPEMULTIPART)
    {
      if (a->encoding != ENC7BIT)
      {
        a->encoding = ENC7BIT;
	convert_to_7bit(a->parts);
      }
      else if (option (OPTPGPSTRICTENC))
	convert_to_7bit (a->parts);
    } 
    else if (a->type == TYPEMESSAGE
	     && ascii_strcasecmp(a->subtype, "delivery-status"))
    {
      if(a->encoding != ENC7BIT)
	mutt_message_to_7bit(a, NULL);
    }
    else if (a->encoding == ENC8BIT)
      a->encoding = ENCQUOTEDPRINTABLE;
    else if (a->encoding == ENCBINARY)
      a->encoding = ENCBASE64;
    else if (a->content && a->encoding != ENCBASE64 &&
	     (a->content->from || (a->content->space && 
				   option (OPTPGPSTRICTENC))))
      a->encoding = ENCQUOTEDPRINTABLE;
    a = a->next;
  }
}

static BODY *pgp_sign_message (BODY *a)
{
  BODY *t;
  char buffer[LONG_STRING];
  char sigfile[_POSIX_PATH_MAX], signedfile[_POSIX_PATH_MAX];
  FILE *pgpin, *pgpout, *pgperr, *fp, *sfp;
  int err = 0;
  int empty = 1;
  pid_t thepid;
  
  convert_to_7bit (a); /* Signed data _must_ be in 7-bit format. */

  mutt_mktemp (sigfile);
  if ((fp = safe_fopen (sigfile, "w")) == NULL)
  {
    return (NULL);
  }

  mutt_mktemp (signedfile);
  if ((sfp = safe_fopen(signedfile, "w")) == NULL)
  {
    mutt_perror(signedfile);
    fclose(fp);
    unlink(sigfile);
    return NULL;
  }
  
  mutt_write_mime_header (a, sfp);
  fputc ('\n', sfp);
  mutt_write_mime_body (a, sfp);
  fclose(sfp);
  
  if ((thepid = pgp_invoke_sign (&pgpin, &pgpout, &pgperr,
				 -1, -1, -1, signedfile)) == -1)
  {
    mutt_perror _("Can't open PGP subprocess!");
    fclose(fp);
    unlink(sigfile);
    unlink(signedfile);
    return NULL;
  }
  
  fputs(PgpPass, pgpin);
  fputc('\n', pgpin);
  fclose(pgpin);
  
  /*
   * Read back the PGP signature.  Also, change MESSAGE=>SIGNATURE as
   * recommended for future releases of PGP.
   */
  while (fgets (buffer, sizeof (buffer) - 1, pgpout) != NULL)
