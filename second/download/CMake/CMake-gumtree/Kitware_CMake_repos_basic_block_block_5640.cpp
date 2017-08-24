{
  case CURLM_CALL_MULTI_PERFORM:
    return "Please call curl_multi_perform() soon";

  case CURLM_OK:
    return "No error";

  case CURLM_BAD_HANDLE:
    return "Invalid multi handle";

  case CURLM_BAD_EASY_HANDLE:
    return "Invalid easy handle";

  case CURLM_OUT_OF_MEMORY:
    return "Out of memory";

  case CURLM_INTERNAL_ERROR:
    return "Internal error";

  case CURLM_BAD_SOCKET:
    return "Invalid socket argument";

  case CURLM_UNKNOWN_OPTION:
    return "Unknown option";

  case CURLM_ADDED_ALREADY:
    return "The easy handle is already added to a multi handle";

  case CURLM_LAST:
    break;
  }