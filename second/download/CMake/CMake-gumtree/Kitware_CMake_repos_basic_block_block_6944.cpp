{
  case CURLE_OK:
    break;
  case CURLE_AGAIN:
    if(!blocking)
      /* CURLE_AGAIN in non-blocking mode is not an error */
      return CURLE_OK;
    /* fall through */
  default:
    return result;
  }