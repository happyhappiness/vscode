      case 'p': /* --ignore-content-length */
        config->ignorecl ^= TRUE;
        break;
      case 'q': /* --ftp-skip-pasv-ip */
        config->ftp_skip_ip ^= TRUE;
        break;
      }
      break;
    case '#': /* --progress-bar */
      config->progressmode ^= CURL_PROGRESS_BAR;
      break;
    case '0':
