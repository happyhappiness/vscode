      gpgme_subkey_t subkey = NULL;

      for (idx = 1, subkey = key->subkeys; subkey;
           idx++, subkey = subkey->next)
        {
	  s = subkey->keyid;
	  
          putc ('\n', fp);
          if ( strlen (s) == 16)
            s += 8; /* display only the short keyID */
          /* L10N: DOTFILL */
          fprintf (fp, _("Subkey ....: 0x%s"), s);
	  if (subkey->revoked)
            {
              putc (' ', fp);
              fputs (_("[Revoked]"), fp);
            }
	  if (subkey->invalid)
            {
              putc (' ', fp);
              fputs (_("[Invalid]"), fp);
            }
	  if (subkey->expired)
            {
              putc (' ', fp);
              fputs (_("[Expired]"), fp);
            }
	  if (subkey->disabled)
            {
              putc (' ', fp);
              fputs (_("[Disabled]"), fp);
            }
          putc ('\n', fp);

	  if (subkey->timestamp > 0)
	    {
