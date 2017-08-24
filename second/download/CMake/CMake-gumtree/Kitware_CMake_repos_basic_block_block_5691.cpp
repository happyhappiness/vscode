h(tn->usq[option]) {
    case CURL_EMPTY:
      tn->us[option] = CURL_YES;
      if(tn->subnegotiation[option] == CURL_YES) {
        /* transmission of data option */
        sendsuboption(conn, option);
      }
      break;
    case CURL_OPPOSITE:
      tn->us[option] = CURL_WANTNO;
      tn->himq[option] = CURL_EMPTY;
      send_negotiation(conn, CURL_WONT, option);
      break;
    }