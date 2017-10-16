      }
      break;
    case 'k': /* allow insecure SSL connects */
      config->insecure_ok ^= TRUE;
      break;
    case 'K': /* parse config file */
      parseconfig(nextarg, config);
      break;
    case 'l':
      config->conf ^= CONF_FTPLISTONLY; /* only list the names of the FTP dir */
      break;
    case 'L':
      config->conf ^= CONF_FOLLOWLOCATION; /* Follow Location: HTTP headers */
