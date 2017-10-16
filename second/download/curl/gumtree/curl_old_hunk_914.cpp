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
