          /*
           * Now, copy cleartext to the screen.  NOTE - we expect that PGP
           * outputs utf-8 cleartext.  This may not always be true, but it 
           * seems to be a reasonable guess.
           */
          
          if(s->flags & M_DISPLAY)
            {
              if (needpass)
            state_attach_puts (_("[-- BEGIN PGP MESSAGE --]\n\n"), s);
              else if (pgp_keyblock)
                state_attach_puts (_("[-- BEGIN PGP PUBLIC KEY BLOCK --]\n"),
                                   s);
