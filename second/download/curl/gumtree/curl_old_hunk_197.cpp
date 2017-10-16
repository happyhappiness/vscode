        break;
      }
      if(err)
        return err;
      break;
    case 'r':
      /* byte range requested */
      GetStr(&config->range, nextarg);
      break;
    case 'R':
      /* use remote file's time */
      config->remote_time ^= TRUE;
      break;
    case 's':
