{
      case CURL_WILL:
        tn->telrcv_state = CURL_TS_WILL;
        break;
      case CURL_WONT:
        tn->telrcv_state = CURL_TS_WONT;
        break;
      case CURL_DO:
        tn->telrcv_state = CURL_TS_DO;
        break;
      case CURL_DONT:
        tn->telrcv_state = CURL_TS_DONT;
        break;
      case CURL_SB:
        CURL_SB_CLEAR(tn);
        tn->telrcv_state = CURL_TS_SB;
        break;
      case CURL_IAC:
        tn->telrcv_state = CURL_TS_DATA;
        writebyte();
        break;
      case CURL_DM:
      case CURL_NOP:
      case CURL_GA:
      default:
        tn->telrcv_state = CURL_TS_DATA;
        printoption(data, "RCVD", CURL_IAC, c);
        break;
      }