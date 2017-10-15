                   if (c == '\n' && s->prefix)
                     state_puts (s->prefix, s);
                 }
               fgetconv_close (&fc);
             }
           
-          if (s->flags & M_DISPLAY)
+          if (s->flags & MUTT_DISPLAY)
             {
               state_putc ('\n', s);
               if (needpass)
                 state_attach_puts (_("[-- END PGP MESSAGE --]\n"), s);
               else if (pgp_keyblock)
                 state_attach_puts (_("[-- END PGP PUBLIC KEY BLOCK --]\n"), s);
