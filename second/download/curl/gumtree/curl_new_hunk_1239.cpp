
    case 'g': /* g disables URLglobbing */
      config->globoff = toggle;
      break;

    case 'G': /* HTTP GET */
      if(subletter == 'a') { /* --request-target */
        GetStr(&config->request_target, nextarg);
      }
      else
        config->use_httpget = TRUE;
      break;

    case 'h': /* h for help */
      if(toggle) {
        return PARAM_HELP_REQUESTED;
      }
      /* we now actually support --no-help too! */
      break;
    case 'H':
      /* A custom header to append to a list */
      if(nextarg[0] == '@') {
        /* read many headers from a file or stdin */
        char *string;
        size_t len;
        bool use_stdin = !strcmp(&nextarg[1], "-");
        FILE *file = use_stdin?stdin:fopen(&nextarg[1], FOPEN_READTEXT);
        if(!file)
          warnf(global, "Failed to open %s!\n", &nextarg[1]);
        else {
          err = file2memory(&string, &len, file);
          if(!err) {
            /* Allow strtok() here since this isn't used threaded */
            /* !checksrc! disable BANNEDFUNC 2 */
            char *h = strtok(string, "\r\n");
            while(h) {
              if(subletter == 'p') /* --proxy-header */
                err = add2list(&config->proxyheaders, h);
              else
                err = add2list(&config->headers, h);
              if(err)
                break;
              h = strtok(NULL, "\r\n");
            }
            free(string);
          }
          if(!use_stdin)
            fclose(file);
          if(err)
            return err;
        }
      }
      else {
        if(subletter == 'p') /* --proxy-header */
          err = add2list(&config->proxyheaders, nextarg);
        else
          err = add2list(&config->headers, nextarg);
        if(err)
          return err;
      }
      break;
    case 'i':
      config->include_headers = toggle; /* include the headers as well in the
                                           general output stream */
      break;
    case 'j':
