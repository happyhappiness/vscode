       tm = localtime (&tt);
 #ifdef HAVE_LANGINFO_D_T_FMT
       strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
 #else
       strftime (shortbuf, sizeof shortbuf, "%c", tm);
 #endif
+      /* L10N: DOTFILL */
       fprintf (fp, _("Valid To ..: %s\n"), shortbuf);
     }
 
   if (key->subkeys)
     s = gpgme_pubkey_algo_name (key->subkeys->pubkey_algo);
   else
