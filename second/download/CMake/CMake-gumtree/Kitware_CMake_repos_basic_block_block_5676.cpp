{
    case CURL_EMPTY:
      /* Error: DONT answered by WILL */
      tn->him[option] = CURL_NO;
      break;
    case CURL_OPPOSITE:
      /* Error: DONT answered by WILL */
      tn->him[option] = CURL_YES;
      tn->himq[option] = CURL_EMPTY;
      break;
    }