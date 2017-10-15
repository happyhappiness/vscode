 
   if (Signature && (tmpfp = mutt_open_read (Signature, &thepid)))
   {
     if (option (OPTSIGDASHES))
       fputs ("\n-- \n", f);
     mutt_copy_stream (tmpfp, f);
-    fclose (tmpfp);
+    safe_fclose (&tmpfp);
     if (thepid != -1)
       mutt_wait_filter (thepid);
   }
 }
 
 /* compare two e-mail addresses and return 1 if they are equivalent */
