        nextarg++; /* pass the @ */
        if(curlx_strequal("-", nextarg))
          file = stdin;
        else
          file = fopen(nextarg, "r");
        config->writeout = file2string(file);
        if(file && (file != stdin))
          fclose(file);
      }
      else
        GetStr(&config->writeout, nextarg);
      break;
