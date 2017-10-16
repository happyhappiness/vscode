      case 'G': /* --delegation LEVEL */
        config->gssapi_delegation = delegation(config, nextarg);
        break;
      case 'H': /* --mail-auth */
        GetStr(&config->mail_auth, nextarg);
        break;
      }
      break;
    case '#': /* --progress-bar */
      if(toggle)
        config->progressmode = CURL_PROGRESS_BAR;
      else
