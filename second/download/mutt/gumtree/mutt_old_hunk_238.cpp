        if (!clearsign && (!pgpout || c == EOF))
	{
	  could_not_decrypt = 1;
	  pgp_void_passphrase ();
	}
	
	if (could_not_decrypt && !(s->flags & M_DISPLAY))
	{
          mutt_error _("Could not decrypt PGP message");
	  mutt_sleep (1);
	  rc = -1;
	  goto out;
        }
      }
      
      /*
       * Now, copy cleartext to the screen.
       */

      if(s->flags & M_DISPLAY)
      {
	if (needpass)
	  state_attach_puts (_("[-- BEGIN PGP MESSAGE --]\n\n"), s);
	else if (pgp_keyblock)
	  state_attach_puts (_("[-- BEGIN PGP PUBLIC KEY BLOCK --]\n"), s);
	else
