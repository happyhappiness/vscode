int pgp_gpgme_application_handler (BODY *m, STATE *s)
{
  int needpass = -1, pgp_keyblock = 0;
  int clearsign = 0;
  long bytes;
  LOFF_T last_pos, offset;
  char buf[HUGE_STRING];
  FILE *pgpout = NULL;

  gpgme_error_t err = 0;
  gpgme_data_t armored_data = NULL;

  short maybe_goodsig = 1;
  short have_any_sigs = 0;

  char body_charset[STRING];  /* Only used for clearsigned messages. */

  dprint (2, (debugfile, "Entering pgp_application_pgp handler\n"));

  /* For clearsigned messages we won't be able to get a character set
     but we know that this may only be text thus we assume Latin-1
     here. */
  if (!mutt_get_body_charset (body_charset, sizeof (body_charset), m))
    strfcpy (body_charset, "iso-8859-1", sizeof body_charset);

  fseeko (s->fpin, m->offset, 0);
  last_pos = m->offset;
  
  for (bytes = m->length; bytes > 0;)
    {
      if (fgets (buf, sizeof (buf), s->fpin) == NULL)
        break;
      
      offset = ftello (s->fpin);
      bytes -= (offset - last_pos); /* don't rely on mutt_strlen(buf) */
      last_pos = offset;
      
      if (!mutt_strncmp ("-----BEGIN PGP ", buf, 15))
        {
          clearsign = 0;
          
          if (MESSAGE(buf + 15))
            needpass = 1;
          else if (SIGNED_MESSAGE(buf + 15))
            {
              clearsign = 1;
              needpass = 0;
            }
          else if (PUBLIC_KEY_BLOCK(buf + 15))
          {
            needpass = 0;
            pgp_keyblock = 1;
          } 
          else
            {
              /* XXX - we may wish to recode here */
              if (s->prefix)
                state_puts (s->prefix, s);
              state_puts (buf, s);
              continue;
            }
          
          have_any_sigs = (have_any_sigs
                           || (clearsign && (s->flags & MUTT_VERIFY)));
          
          /* Copy PGP material to an data container */
	  armored_data = file_to_data_object (s->fpin, m->offset, m->length);
          /* Invoke PGP if needed */
          if (pgp_keyblock)
          {
            pgp_gpgme_extract_keys (armored_data, &pgpout, 1);
          }
          else if (!clearsign || (s->flags & MUTT_VERIFY))
            {
              unsigned int sig_stat = 0;
              gpgme_data_t plaintext;
              gpgme_ctx_t ctx;

              plaintext = create_gpgme_data ();
              ctx = create_gpgme_context (0);

              if (clearsign)
                err = gpgme_op_verify (ctx, armored_data, NULL, plaintext);
              else
                {
                  err = gpgme_op_decrypt_verify (ctx, armored_data, plaintext);
                  if (gpg_err_code (err) == GPG_ERR_NO_DATA)
                    {
                      /* Decrypt verify can't handle signed only messages. */
		      err = (gpgme_data_seek (armored_data, 0, SEEK_SET) == -1)
			? gpgme_error_from_errno (errno) : 0;
                      /* Must release plaintext so that we supply an
                         uninitialized object. */
                      gpgme_data_release (plaintext);
                      plaintext = create_gpgme_data ();
                      err = gpgme_op_verify (ctx, armored_data,
                                             NULL, plaintext);
                    }
                }
              mutt_need_hard_redraw ();

              if (err)
                {
                  char errbuf[200];
                  
                  snprintf (errbuf, sizeof(errbuf)-1, 
                            _("Error: decryption/verification failed: %s\n"),
                            gpgme_strerror (err));
                  state_attach_puts (errbuf, s);
                }
              else
                { /* Decryption/Verification succeeded */
                  char *tmpfname;

		  {
		    /* Check whether signatures have been verified.  */
		    gpgme_verify_result_t verify_result;

                    verify_result = gpgme_op_verify_result (ctx);
		    if (verify_result->signatures)
		      sig_stat = 1;
		  }

                  have_any_sigs = 0;
                  maybe_goodsig = 0;
                  if ((s->flags & MUTT_DISPLAY) && sig_stat)
                    {
                      int res, idx;
                      int anybad = 0;

                      state_attach_puts (_("[-- Begin signature "
                                           "information --]\n"), s);
                      have_any_sigs = 1;
                      for(idx=0;
                          (res = show_one_sig_status (ctx, idx, s)) != -1;
                          idx++)
                        {
                          if (res == 1)
                            anybad = 1;
                        }
                      if (!anybad && idx)
                        maybe_goodsig = 1;
                      
                      state_attach_puts (_("[-- End signature "
                                           "information --]\n\n"), s);
                    }

                  tmpfname = data_object_to_tempfile (plaintext, NULL, &pgpout);
                  if (!tmpfname)
                    {
                      pgpout = NULL;
                      state_attach_puts (_("Error: copy data failed\n"), s);
                    }
                  else
                    {
                      unlink (tmpfname);
                      FREE (&tmpfname);
                    }
                }
              gpgme_data_release (plaintext);
              gpgme_release (ctx);
            }
      
          /*
           * Now, copy cleartext to the screen.  NOTE - we expect that PGP
           * outputs utf-8 cleartext.  This may not always be true, but it 
           * seems to be a reasonable guess.
           */
          
          if(s->flags & MUTT_DISPLAY)
            {
              if (needpass)
            state_attach_puts (_("[-- BEGIN PGP MESSAGE --]\n\n"), s);
              else if (pgp_keyblock)
                state_attach_puts (_("[-- BEGIN PGP PUBLIC KEY BLOCK --]\n"),
                                   s);
              else
                state_attach_puts (_("[-- BEGIN PGP SIGNED MESSAGE --]\n\n"),
                                   s);
            }
          
          if (clearsign)
            {
              copy_clearsigned (armored_data, s, body_charset);
            }
          else if (pgpout)
            {
              FGETCONV *fc;
              int c;
              rewind (pgpout);
              fc = fgetconv_open (pgpout, "utf-8", Charset, 0);
              while ((c = fgetconv (fc)) != EOF)
                {
                  state_putc (c, s);
                  if (c == '\n' && s->prefix)
                    state_puts (s->prefix, s);
                }
              fgetconv_close (&fc);
            }
          
          if (s->flags & MUTT_DISPLAY)
            {
              state_putc ('\n', s);
              if (needpass)
                state_attach_puts (_("[-- END PGP MESSAGE --]\n"), s);
              else if (pgp_keyblock)
                state_attach_puts (_("[-- END PGP PUBLIC KEY BLOCK --]\n"), s);
              else
                state_attach_puts (_("[-- END PGP SIGNED MESSAGE --]\n"), s);
            }
          
          gpgme_data_release (armored_data);
          if (pgpout)
            {
              safe_fclose (&pgpout);
            }
        }
      else
      {
	/* A traditional PGP part may mix signed and unsigned content */
        /* XXX - we may wish to recode here */
        if (s->prefix)
          state_puts (s->prefix, s);
        state_puts (buf, s);
      }
    }

  m->goodsig = (maybe_goodsig && have_any_sigs);
  
  if (needpass == -1)
    {
      state_attach_puts (_("[-- Error: could not find beginning"
                           " of PGP message! --]\n\n"), s);
      return 1;
    }
  dprint (2, (debugfile, "Leaving pgp_application_pgp handler\n"));

  return err;
}