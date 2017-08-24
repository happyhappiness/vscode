h(tn->usq[option]) {
      case CURL_EMPTY:
        /* Error: already negotiating for enable */
        break;
      case CURL_OPPOSITE:
        tn->usq[option] = CURL_EMPTY;
        break;
      }