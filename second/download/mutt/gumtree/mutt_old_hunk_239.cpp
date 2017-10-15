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
	  if (could_not_decrypt)
