                        maybe_goodsig = 1;
                      
                      state_attach_puts (_("[-- End signature "
                                           "information --]\n\n"), s);
                    }

                  tmpfname = data_object_to_tempfile (plaintext, &pgpout);
                  if (!tmpfname)
                    {
                      pgpout = NULL;
                      state_attach_puts (_("Error: copy data failed\n"), s);
                    }
                  else
                    {
                      unlink (tmpfname);
                      FREE (&tmpfname);
                    }
                }
              gpgme_release (ctx);
            }
      
          /*
           * Now, copy cleartext to the screen.  NOTE - we expect that PGP
           * outputs utf-8 cleartext.  This may not always be true, but it 
