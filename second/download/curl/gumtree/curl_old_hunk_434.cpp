    case 'w':
      /* get the output string */
      if('@' == *nextarg) {
        /* the data begins with a '@' letter, it means that a file name
           or - (stdin) follows */
        FILE *file;
        nextarg++; /* pass the @ */
        if(curlx_strequal("-", nextarg))
          file = stdin;
        else
          file = fopen(nextarg, "r");
        err = file2string(&config->writeout, file);
        if(file && (file != stdin))
          fclose(file);
        if(err)
          return err;
        if(!config->writeout)
          warnf(config, "Failed to read %s", file);
      }
      else
        GetStr(&config->writeout, nextarg);
      break;
    case 'x':
      /* proxy */
