       fpr = sig->fpr;
       sum = sig->summary;
 
       if (gpg_err_code (sig->status) != GPG_ERR_NO_ERROR)
 	anybad = 1;
 
-      err = gpgme_get_key (ctx, fpr, &key, 0); /* secret key?  */
-      if (! err)
+      if (gpg_err_code (sig->status) != GPG_ERR_NO_PUBKEY)
+      {
+	err = gpgme_get_key (ctx, fpr, &key, 0); /* secret key?  */
+	if (! err)
 	{
 	  if (! signature_key)
 	    signature_key = key;
 	}
-      else
-       {
+	else
+	{
           key = NULL; /* Old gpgme versions did not set KEY to NULL on
                          error.   Do it here to avoid a double free. */
-       }
+	}
+      }
+      else
+      {
+	/* pubkey not present */
+      }
 
       if (!s || !s->fpout || !(s->flags & M_DISPLAY))
 	; /* No state information so no way to print anything. */
       else if (err)
 	{
-          state_attach_puts (_("Error getting key information: "), s);
+          state_attach_puts (_("Error getting key information for KeyID "), s);
+	  state_attach_puts ( fpr, s );
+          state_attach_puts (_(": "), s);
           state_attach_puts ( gpgme_strerror (err), s );
           state_attach_puts ("\n", s);
           anybad = 1;
 	}
       else if ((sum & GPGME_SIGSUM_GREEN))
       {
