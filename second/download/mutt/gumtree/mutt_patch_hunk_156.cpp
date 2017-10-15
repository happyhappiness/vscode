 
   s2 = is_pgp ? "PGP" : "X.509";
 
   if (key->subkeys)
     aval = key->subkeys->length;
 
+  /* L10N: DOTFILL */
   fprintf (fp, _("Key Type ..: %s, %lu bit %s\n"), s2, aval, s);
 
+  /* L10N: DOTFILL */
   fprintf (fp, _("Key Usage .: "));
   delim = "";
 
   if (key_check_cap (key, KEY_CAP_CAN_ENCRYPT))
     {
       fprintf (fp, "%s%s", delim, _("encryption"));
