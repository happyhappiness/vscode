          return PARAM_BAD_USE;
        else if(rc == 1)
          config->localportrange = 1; /* default number of ports to try */
        else {
          config->localportrange -= config->localport;
          if(config->localportrange < 1) {
            warnf(config, "bad range input\n");
            return PARAM_BAD_USE;
          }
        }
        break;
      case 'u': /* --ftp-alternative-to-user */
        GetStr(&config->ftp_alternative_to_user, nextarg);
