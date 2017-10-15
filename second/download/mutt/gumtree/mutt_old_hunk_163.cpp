      gpgme_op_keylist_end (listctx);
      
      print_key_info (k, fp);
      if (!--maxdepth)
        {
          putc ('\n', fp);
          fputs (_("Error: certification chain to long - stopping here\n"),
                 fp);
          break;
        }
    }

 leave:
