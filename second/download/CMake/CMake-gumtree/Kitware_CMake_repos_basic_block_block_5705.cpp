h(pointer[0]) {
      case CURL_TELOPT_TTYPE:
      case CURL_TELOPT_XDISPLOC:
      case CURL_TELOPT_NEW_ENVIRON:
      case CURL_TELOPT_NAWS:
        infof(data, "%s", CURL_TELOPT(pointer[0]));
        break;
      default:
        infof(data, "%s (unsupported)", CURL_TELOPT(pointer[0]));
        break;
      }