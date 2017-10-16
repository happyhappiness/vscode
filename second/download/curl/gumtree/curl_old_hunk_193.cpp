        break;
      case 'i': /* --limit-rate */
        {
          /* We support G, M, K too */
          char *unit;
          curl_off_t value = curlx_strtoofft(nextarg, &unit, 0);
          switch(nextarg[strlen(nextarg)-1]) {
          case 'G':
          case 'g':
            value *= 1024*1024*1024;
            break;
          case 'M':
          case 'm':
            value *= 1024*1024;
            break;
          case 'K':
          case 'k':
            value *= 1024;
            break;
          }
          config->recvpersecond = value;
          config->sendpersecond = value;
        }
        break;

