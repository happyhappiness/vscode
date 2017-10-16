    case 'w':
      /* get the output string */
      if('@' == *nextarg) {
        /* the data begins with a '@' letter, it means that a file name
           or - (stdin) follows */
        FILE *file;
        const char *fname;
        nextarg++; /* pass the @ */
        if(curlx_strequal("-", nextarg)) {
          fname = "<stdin>";
          file = stdin;
        }
        else {
          fname = nextarg;
          file = fopen(nextarg, "r");
        }
        err = file2string(&config->writeout, file);
        if(file && (file != stdin))
          fclose(file);
        if(err)
          return err;
        if(!config->writeout)
          warnf(config, "Failed to read %s", fname);
      }
      else
        GetStr(&config->writeout, nextarg);
      break;
    case 'x':
      /* proxy */
