                     }
 
                   tmpfname = data_object_to_tempfile (plaintext, NULL, &pgpout);
                   if (!tmpfname)
                     {
                       pgpout = NULL;
-                      state_attach_puts (_("Error: copy data failed\n"), s);
+                      state_puts (_("Error: copy data failed\n"), s);
                     }
                   else
                     {
                       unlink (tmpfname);
                       FREE (&tmpfname);
                     }
