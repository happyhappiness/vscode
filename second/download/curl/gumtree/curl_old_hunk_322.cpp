        if(str2num(&config->maxredirs, nextarg))
          return PARAM_BAD_NUMERIC;
        break;

      case 't': /* --proxy-ntlm */
        if(curlinfo->features & CURL_VERSION_NTLM)
          config->proxyntlm ^= TRUE;
        else
          return PARAM_LIBCURL_DOESNT_SUPPORT;
        break;

      case 'u': /* --crlf */
        /* LF -> CRLF conversinon? */
        config->crlf = TRUE;
        break;

      case 'v': /* --stderr */
        if(strcmp(nextarg, "-")) {
          FILE *newfile = fopen(nextarg, "wt");
          if(!newfile)
            warnf(config, "Failed to open %s!\n", nextarg);
          else {
            config->errors = newfile;
            config->errors_fopened = TRUE;
          }
        }
        else
          config->errors = stdout;
