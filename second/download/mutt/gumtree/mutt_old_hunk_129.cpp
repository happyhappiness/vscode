                      warn_s = N_("ID is only marginally valid.");
                      break;
                    case GPGME_VALIDITY_FULL:      
                    case GPGME_VALIDITY_ULTIMATE:  
                      break;
                    }

                  snprintf (buff, sizeof (buff),
                            _("%s Do you really want to use the key?"),
                            _(warn_s));
		  
                  if (mutt_yesorno (buff, 0) != 1)
                    {
                      mutt_clear_error ();
                      break;
                    }
                  *forced_valid = 1;
                }
            }  

          k = crypt_copy_key (key_table[menu->current]);
          done = 1;
          break;
          
