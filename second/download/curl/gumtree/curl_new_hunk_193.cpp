        break;
      case 'i': /* --limit-rate */
        {
          /* We support G, M, K too */
          char *unit;
          curl_off_t value = curlx_strtoofft(nextarg, &unit, 0);

          if(!*unit)
            unit=(char *)"b";
          else if(strlen(unit) > 1)
            unit=(char *)"w"; /* unsupported */

          switch(*unit) {
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
          case 'b':
          case 'B':
            /* for plain bytes, leave as-is */
            break;
          default:
            warnf(config, "unsupported rate unit. Use G, M, K or B!\n");
            return PARAM_BAD_USE;
          }
          config->recvpersecond = value;
          config->sendpersecond = value;
        }
        break;

