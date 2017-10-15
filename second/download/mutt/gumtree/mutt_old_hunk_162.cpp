
	  if (subkey)
	    aval = subkey->length;
	  else
	    aval = 0;

          fprintf (fp, _("Key Type ..: %s, %lu bit %s\n"), "PGP", aval, s);

          fprintf (fp, _("Key Usage .: "));
          delim = "";

	  if (subkey->can_encrypt)
            {
              fprintf (fp, "%s%s", delim, _("encryption"));
