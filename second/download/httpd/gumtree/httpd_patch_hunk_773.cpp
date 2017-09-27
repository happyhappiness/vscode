     /*
      * Let the user know when we're successful.
      */
     if (nPassPhraseDialog > 0) {
         sc = mySrvConfig(s);
         if (writetty) {
-            apr_file_printf(writetty, "\n");
-            apr_file_printf(writetty, "Ok: Pass Phrase Dialog successful.\n");
+            apr_file_printf(writetty, "\n"
+                            "OK: Pass Phrase Dialog successful.\n");
         }
     }
 
     /*
      * Wipe out the used memory from the
      * pass phrase array and then deallocate it
