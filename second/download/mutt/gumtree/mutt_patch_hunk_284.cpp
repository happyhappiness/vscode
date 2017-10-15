       tm = localtime (&tt);
 #ifdef HAVE_LANGINFO_D_T_FMT
       strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
 #else
       strftime (shortbuf, sizeof shortbuf, "%c", tm);
 #endif
-      /* L10N: DOTFILL */
-      fprintf (fp, _("Valid From : %s\n"), shortbuf);
+      fprintf (fp, "%*s%s\n", KeyInfoPadding[KIP_VALID_FROM],
+               _(KeyInfoPrompts[KIP_VALID_FROM]), shortbuf);
     }
-  
+
   if (key->subkeys && (key->subkeys->expires > 0))
     {
       tt = key->subkeys->expires;
-      
+
       tm = localtime (&tt);
 #ifdef HAVE_LANGINFO_D_T_FMT
       strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
 #else
       strftime (shortbuf, sizeof shortbuf, "%c", tm);
 #endif
-      /* L10N: DOTFILL */
-      fprintf (fp, _("Valid To ..: %s\n"), shortbuf);
+      fprintf (fp, "%*s%s\n", KeyInfoPadding[KIP_VALID_TO],
+               _(KeyInfoPrompts[KIP_VALID_TO]), shortbuf);
     }
 
   if (key->subkeys)
     s = gpgme_pubkey_algo_name (key->subkeys->pubkey_algo);
   else
     s = "?";
 
   s2 = is_pgp ? "PGP" : "X.509";
 
   if (key->subkeys)
     aval = key->subkeys->length;
 
-  /* L10N: DOTFILL */
-  fprintf (fp, _("Key Type ..: %s, %lu bit %s\n"), s2, aval, s);
+  fprintf (fp, "%*s", KeyInfoPadding[KIP_KEY_TYPE],
+           _(KeyInfoPrompts[KIP_KEY_TYPE]));
+  /* L10N: This is printed after "Key Type: " and looks like this:
+   *       PGP, 2048 bit RSA */
+  fprintf (fp, _("%s, %lu bit %s\n"), s2, aval, s);
 
-  /* L10N: DOTFILL */
-  fprintf (fp, _("Key Usage .: "));
+  fprintf (fp, "%*s", KeyInfoPadding[KIP_KEY_USAGE],
+           _(KeyInfoPrompts[KIP_KEY_USAGE]));
   delim = "";
 
   if (key_check_cap (key, KEY_CAP_CAN_ENCRYPT))
     {
+      /* L10N: value in Key Usage: field */
       fprintf (fp, "%s%s", delim, _("encryption"));
       delim = _(", ");
     }
   if (key_check_cap (key, KEY_CAP_CAN_SIGN))
     {
+      /* L10N: value in Key Usage: field */
       fprintf (fp, "%s%s", delim, _("signing"));
       delim = _(", ");
     }
   if (key_check_cap (key, KEY_CAP_CAN_CERTIFY))
     {
+      /* L10N: value in Key Usage: field */
       fprintf (fp, "%s%s", delim, _("certification"));
       delim = _(", ");
     }
   putc ('\n', fp);
 
   if (key->subkeys)
     {
       s = key->subkeys->fpr;
-      /* L10N: DOTFILL */
-      fputs (_("Fingerprint: "), fp);
+      fprintf (fp, "%*s", KeyInfoPadding[KIP_FINGERPRINT],
+               _(KeyInfoPrompts[KIP_FINGERPRINT]));
       if (is_pgp && strlen (s) == 40)
         {
           for (i=0; *s && s[1] && s[2] && s[3] && s[4]; s += 4, i++)
             {
               putc (*s, fp);
               putc (s[1], fp);
