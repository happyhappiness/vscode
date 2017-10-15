     {
       char buf[200];
       
       snprintf (buf, sizeof(buf)-1, 
                 _("Error: verification failed: %s\n"),
                 gpgme_strerror (err));
-      state_attach_puts (buf, s);
+      state_puts (buf, s);
     }
   else
     { /* Verification succeeded, see what the result is. */
       int res, idx;
       int anybad = 0;
+      gpgme_verify_result_t verify_result;
 
       if (signature_key)
 	{
 	  gpgme_key_unref (signature_key);
 	  signature_key = NULL;
 	}
 
-      for(idx=0; (res = show_one_sig_status (ctx, idx, s)) != -1; idx++)
+      verify_result = gpgme_op_verify_result (ctx);
+      if (verify_result && verify_result->signatures)
+      {
+        for (idx=0; (res = show_one_sig_status (ctx, idx, s)) != -1; idx++)
         {
           if (res == 1)
             anybad = 1;
           else if (res == 2)
             anywarn = 2;
         }
-      if (!anybad)
-        badsig = 0;
+        if (!anybad)
+          badsig = 0;
+      }
     }
 
   if (!badsig)
     {
       gpgme_verify_result_t result;
       gpgme_sig_notation_t notation;
