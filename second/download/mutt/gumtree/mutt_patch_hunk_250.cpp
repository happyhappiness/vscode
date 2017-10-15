   if ((type & ENCRYPT) &&
       (thepid = smime_invoke_decrypt (&smimein, NULL, NULL, -1,
 				      fileno (smimeout),  fileno (smimeerr), tmpfname)) == -1)
   {
     safe_fclose (&smimeout); smimeout = NULL;
     mutt_unlink (tmpfname);
-    if (s->flags & M_DISPLAY)
+    if (s->flags & MUTT_DISPLAY)
       state_attach_puts (_("[-- Error: unable to create OpenSSL subprocess! --]\n"), s);
     return NULL;
   }
   else if ((type & SIGNOPAQUE) &&
 	   (thepid = smime_invoke_verify (&smimein, NULL, NULL, -1,
 					  fileno (smimeout), fileno (smimeerr), NULL,
 					  tmpfname, SIGNOPAQUE)) == -1)
   {
     safe_fclose (&smimeout); smimeout = NULL;
     mutt_unlink (tmpfname);
-    if (s->flags & M_DISPLAY)
+    if (s->flags & MUTT_DISPLAY)
       state_attach_puts (_("[-- Error: unable to create OpenSSL subprocess! --]\n"), s);
     return NULL;
   }
 
   
   if (type & ENCRYPT)
