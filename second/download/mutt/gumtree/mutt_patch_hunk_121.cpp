   /* Note: We don't need a current time output because GPGME avoids
      such an attack by separating the meta information from the
      data. */
   state_attach_puts (_("[-- Begin signature information --]\n"), s);
 
   err = gpgme_op_verify (ctx, signature, message, NULL);
+  gpgme_data_release (message);
+  gpgme_data_release (signature);
+
   mutt_need_hard_redraw ();
   if (err)
     {
       char buf[200];
       
       snprintf (buf, sizeof(buf)-1, 
