       else if (tattach->goodsig)
         {
           a->goodsig = 1;
           a->warnsig = tattach->warnsig;
         }
 
-      if (s->flags & M_DISPLAY)
+      if (s->flags & MUTT_DISPLAY)
         {
           state_puts ("\n", s);
           state_attach_puts (is_signed?
              _("[-- End of S/MIME signed data --]\n"):
              _("[-- End of S/MIME encrypted data --]\n"),
                              s);
