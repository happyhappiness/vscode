        {
	  s = subkey->keyid;
	  
          putc ('\n', fp);
          if ( strlen (s) == 16)
            s += 8; /* display only the short keyID */
          fprintf (fp, _("Subkey ....: 0x%s"), s);
	  if (subkey->revoked)
            {
              putc (' ', fp);
              fputs (_("[Revoked]"), fp);
            }
