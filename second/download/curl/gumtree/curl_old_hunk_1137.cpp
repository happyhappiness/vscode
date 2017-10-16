          warnf(global, "Failed to read %s", fname);
      }
      else
        GetStr(&config->writeout, nextarg);
      break;
    case 'x':
      /* proxy */
      GetStr(&config->proxy, nextarg);
      config->proxyver = CURLPROXY_HTTP;
      break;
    case 'X':
      /* set custom request */
      GetStr(&config->customrequest, nextarg);
      break;
    case 'y':
