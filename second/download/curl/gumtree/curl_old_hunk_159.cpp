        /* LF -> CRLF conversinon? */
        config->crlf = TRUE;
        break;

      case 'v': /* --stderr */
        if(strcmp(nextarg, "-")) {
          config->errors = fopen(nextarg, "wt");
          config->errors_fopened = TRUE;
        }
        else
          config->errors = stdout;
      break;
      case 'w': /* --interface */
        /* interface */
