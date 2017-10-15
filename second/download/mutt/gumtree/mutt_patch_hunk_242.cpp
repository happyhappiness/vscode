      *
      */
     
     if (mutt_is_multipart_signed (tattach) && !tattach->next)
       a->goodsig |= tattach->goodsig;
     
-    if (s->flags & M_DISPLAY)
+    if (s->flags & MUTT_DISPLAY)
     {
       state_puts ("\n", s);
       state_attach_puts (_("[-- End of PGP/MIME encrypted data --]\n"), s);
     }
 
     mutt_free_body (&tattach);
