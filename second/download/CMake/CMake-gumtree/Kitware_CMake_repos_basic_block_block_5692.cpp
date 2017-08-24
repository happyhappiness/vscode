{
    case CURL_EMPTY:
      tn->us[option] = CURL_NO;
      break;
    case CURL_OPPOSITE:
      tn->us[option] = CURL_NO;
      tn->usq[option] = CURL_EMPTY;
      break;
    }