{
    case CURL_EMPTY:
      tn->him[option] = CURL_NO;
      break;

    case CURL_OPPOSITE:
      tn->him[option] = CURL_WANTYES;
      tn->himq[option] = CURL_EMPTY;
      send_negotiation(conn, CURL_DO, option);
      break;
    }