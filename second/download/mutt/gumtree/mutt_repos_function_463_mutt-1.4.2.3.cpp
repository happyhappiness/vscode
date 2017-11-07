static int pgp_send_menu (int bits, int *redraw)
{
  pgp_key_t *p;
  char input_signas[SHORT_STRING];

  switch (mutt_multi_choice (_("(e)ncrypt, (s)ign, sign (a)s, (b)oth, or (f)orget it? "),
			     _("esabf")))
  {
  case 1: /* (e)ncrypt */
    bits |= PGPENCRYPT;
    break;

  case 2: /* (s)ign */
    bits |= PGPSIGN;
    break;

  case 3: /* sign (a)s */

    unset_option(OPTPGPCHECKTRUST);

    if ((p = pgp_ask_for_key (_("Sign as: "), NULL, KEYFLAG_CANSIGN, PGP_SECRING)))
    {
      snprintf (input_signas, sizeof (input_signas), "0x%s", pgp_keyid (p));
      mutt_str_replace (&PgpSignAs, input_signas);
      pgp_free_key (&p);
      
      bits |= PGPSIGN;
	
      pgp_void_passphrase ();	/* probably need a different passphrase */
    }
    else
    {
      bits &= ~PGPSIGN;
    }

    *redraw = REDRAW_FULL;
    break;

  case 4: /* (b)oth */
    bits = PGPENCRYPT | PGPSIGN;
    break;

  case 5: /* (f)orget it */
    bits = 0;
    break;
  }
  if (!*redraw)
    redraw_pgp_lines (bits);
  return (bits);
}