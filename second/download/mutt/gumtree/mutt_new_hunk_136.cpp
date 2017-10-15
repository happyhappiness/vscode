	fc = fgetconv_open (pgpout, expected_charset, Charset, M_ICONV_HOOK_FROM);
	while ((c = fgetconv (fc)) != EOF)
	  state_prefix_putc (c, s);
	fgetconv_close (&fc);
      }

      /*
       * Multiple PGP blocks can exist, so these need to be closed and
       * unlinked inside the loop.
       */
      safe_fclose (&tmpfp);
      mutt_unlink (tmpfname);
      if (pgpout)
      {
	safe_fclose (&pgpout);
	mutt_unlink (outfile);
      }

      if (s->flags & M_DISPLAY)
      {
	state_putc ('\n', s);
	if (needpass)
        {
	  state_attach_puts (_("[-- END PGP MESSAGE --]\n"), s);
