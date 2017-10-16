        break;

      case 'v': /* --stderr */
        if(strcmp(nextarg, "-")) {
          FILE *newfile = fopen(nextarg, "wt");
          if(!newfile)
            warnf(config, "Failed to open %s!\n", nextarg);
          else {
            if(global->errors_fopened)
              fclose(global->errors);
            global->errors = newfile;
            global->errors_fopened = TRUE;
          }
