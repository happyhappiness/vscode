              else if (pgp_keyblock)
                state_attach_puts (_("[-- END PGP PUBLIC KEY BLOCK --]\n"), s);
              else
                state_attach_puts (_("[-- END PGP SIGNED MESSAGE --]\n"), s);
            }
          
          if (pgpout)
            {
              safe_fclose (&pgpout);
            }
        }
      else
