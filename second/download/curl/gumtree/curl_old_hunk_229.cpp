        config->crlf = TRUE;
        break;

      case 'v': /* --stderr */
        if(strcmp(nextarg, "-")) {
          FILE *newfile = fopen(nextarg, "wt");
          if(!config->errors)
            warnf(config, "Failed to open %s!\n", nextarg);
          else {
            config->errors = newfile;
            config->errors_fopened = TRUE;
          }
        }
