                 {
                   char errbuf[200];
                   
                   snprintf (errbuf, sizeof(errbuf)-1, 
                             _("Error: decryption/verification failed: %s\n"),
                             gpgme_strerror (err));
-                  state_attach_puts (errbuf, s);
+                  state_puts (errbuf, s);
                 }
               else
                 { /* Decryption/Verification succeeded */
                   char *tmpfname;
 
 		  {
