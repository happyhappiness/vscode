{
      case CURL_EMPTY:
        /* Already negotiating for CURL_YES, queue the request */
        tn->himq[option] = CURL_OPPOSITE;
        break;
      case CURL_OPPOSITE:
        /* Error: already queued an enable request */
        break;
      }