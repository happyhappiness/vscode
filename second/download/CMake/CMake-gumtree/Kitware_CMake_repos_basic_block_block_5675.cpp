{
    case CURL_EMPTY:
      tn->him[option] = CURL_YES;
      break;
    case CURL_OPPOSITE:
      tn->him[option] = CURL_WANTNO;
      tn->himq[option] = CURL_EMPTY;
      send_negotiation(conn, CURL_DONT, option);
      break;
    }