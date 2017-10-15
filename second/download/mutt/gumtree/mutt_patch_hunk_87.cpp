   while (fgets (buffer, sizeof (buffer) - 1, pgperr) != NULL)
   {
     err = 1;
     fputs (buffer, stdout);
   }
 
-  mutt_wait_filter (thepid);
-  fclose (pgperr);
-  fclose (pgpout);
+  if(mutt_wait_filter (thepid) && option(OPTPGPCHECKEXIT))
+    empty=1;
+
+  safe_fclose (&pgperr);
+  safe_fclose (&pgpout);
   unlink (signedfile);
   
   if (fclose (fp) != 0)
   {
     mutt_perror ("fclose");
     unlink (sigfile);
