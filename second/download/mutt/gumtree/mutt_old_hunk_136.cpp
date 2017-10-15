	fc = fgetconv_open (pgpout, expected_charset, Charset, M_ICONV_HOOK_FROM);
	while ((c = fgetconv (fc)) != EOF)
	  state_prefix_putc (c, s);
	fgetconv_close (&fc);
      }

      if (s->flags & M_DISPLAY)
      {
	state_putc ('\n', s);
	if (needpass)
        {
	  state_attach_puts (_("[-- END PGP MESSAGE --]\n"), s);
