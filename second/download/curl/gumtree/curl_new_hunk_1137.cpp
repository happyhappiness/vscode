          warnf(global, "Failed to read %s", fname);
      }
      else
        GetStr(&config->writeout, nextarg);
      break;
    case 'x':
      switch(subletter) {
      case 'a': /* --preproxy */
        GetStr(&config->preproxy, nextarg);
        break;
      default:
        /* --proxy */
        GetStr(&config->proxy, nextarg);
        config->proxyver = CURLPROXY_HTTP;
        break;
      }
      break;
    case 'X':
      /* set custom request */
      GetStr(&config->customrequest, nextarg);
      break;
    case 'y':
