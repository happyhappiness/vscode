 
 	  if (subkey)
 	    aval = subkey->length;
 	  else
 	    aval = 0;
 
+          /* L10N: DOTFILL */
           fprintf (fp, _("Key Type ..: %s, %lu bit %s\n"), "PGP", aval, s);
 
+          /* L10N: DOTFILL */
           fprintf (fp, _("Key Usage .: "));
           delim = "";
 
 	  if (subkey->can_encrypt)
             {
               fprintf (fp, "%s%s", delim, _("encryption"));
