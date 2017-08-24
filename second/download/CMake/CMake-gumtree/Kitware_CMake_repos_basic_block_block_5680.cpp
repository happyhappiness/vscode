{
    case CURL_NO:
      /* Already disabled */
      break;

    case CURL_YES:
      tn->us[option] = CURL_WANTNO;
      send_negotiation(conn, CURL_WONT, option);
      break;

    case CURL_WANTNO:
      switch(tn->usq[option]) {
      case CURL_EMPTY:
        /* Already negotiating for NO */
        break;
      case CURL_OPPOSITE:
        tn->usq[option] = CURL_EMPTY;
        break;
      }
      break;

    case CURL_WANTYES:
      switch(tn->usq[option]) {
      case CURL_EMPTY:
        tn->usq[option] = CURL_OPPOSITE;
        break;
      case CURL_OPPOSITE:
        break;
      }
      break;
    }