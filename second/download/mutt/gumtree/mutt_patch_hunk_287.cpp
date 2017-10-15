               tm = localtime (&tt);
 #ifdef HAVE_LANGINFO_D_T_FMT
               strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
 #else
               strftime (shortbuf, sizeof shortbuf, "%c", tm);
 #endif
-              /* L10N: DOTFILL */
-              fprintf (fp, _("Valid From : %s\n"), shortbuf);
+              fprintf (fp, "%*s%s\n", KeyInfoPadding[KIP_VALID_FROM],
+                       _(KeyInfoPrompts[KIP_VALID_FROM]), shortbuf);
             }
 
 	  if (subkey->expires > 0)
 	    {
 	      tt = subkey->expires;
 
               tm = localtime (&tt);
 #ifdef HAVE_LANGINFO_D_T_FMT
               strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
 #else
               strftime (shortbuf, sizeof shortbuf, "%c", tm);
 #endif
-              /* L10N: DOTFILL */
-              fprintf (fp, _("Valid To ..: %s\n"), shortbuf);
+              fprintf (fp, "%*s%s\n", KeyInfoPadding[KIP_VALID_TO],
+                       _(KeyInfoPrompts[KIP_VALID_TO]), shortbuf);
             }
 
 	  if (subkey)
 	    s = gpgme_pubkey_algo_name (subkey->pubkey_algo);
 	  else
             s = "?";
 
 	  if (subkey)
 	    aval = subkey->length;
 	  else
 	    aval = 0;
 
-          /* L10N: DOTFILL */
-          fprintf (fp, _("Key Type ..: %s, %lu bit %s\n"), "PGP", aval, s);
+          fprintf (fp, "%*s", KeyInfoPadding[KIP_KEY_TYPE],
+                   _(KeyInfoPrompts[KIP_KEY_TYPE]));
+          fprintf (fp, _("%s, %lu bit %s\n"), "PGP", aval, s);
 
-          /* L10N: DOTFILL */
-          fprintf (fp, _("Key Usage .: "));
+          fprintf (fp, "%*s", KeyInfoPadding[KIP_KEY_USAGE],
+                   _(KeyInfoPrompts[KIP_KEY_USAGE]));
           delim = "";
 
 	  if (subkey->can_encrypt)
             {
               fprintf (fp, "%s%s", delim, _("encryption"));
               delim = _(", ");
