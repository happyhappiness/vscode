      case 'p': /* --ignore-content-length */
        config->ignorecl ^= TRUE;
        break;
      case 'q': /* --ftp-skip-pasv-ip */
        config->ftp_skip_ip ^= TRUE;
        break;
      case 'r': /* --ftp-method (undocumented at this point) */
        config->ftp_filemethod = ftpfilemethod(config, nextarg);
        break;
      case 's': /* --local-port */
        rc = sscanf(nextarg, "%d - %d",
                    &config->localport,
                    &config->localportrange);
        if(!rc)
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
        break;
      case 'v': /* --ftp-ssl-reqd */
        config->ftp_ssl_reqd ^= TRUE;
        break;
      case 'w': /* --no-sessionid */
        config->disable_sessionid ^= TRUE;
        break;
      case 'x': /* --ftp-ssl-control */
        config->ftp_ssl_control ^= TRUE;
        break;
      }
      break;
    case '#': /* --progress-bar */
      config->progressmode ^= CURL_PROGRESS_BAR;
      break;
    case '0':
