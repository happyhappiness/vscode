        FILE *file;
        nextarg++; /* pass the @ */
        if(curlx_strequal("-", nextarg))
          file = stdin;
        else
          file = fopen(nextarg, "r");
        config->writeout = file2string(file);
        if(!config->writeout)
          warnf(config, "Failed to read %s", file);
        if(file && (file != stdin))
          fclose(file);
      }
      else
        GetStr(&config->writeout, nextarg);
      break;
    case 'x':
      /* proxy */
