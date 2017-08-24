{
  case CURL_SSLVERSION_MAX_NONE:
  case CURL_SSLVERSION_MAX_DEFAULT:
    break;

  default:
    if((data->set.ssl.primary.version_max >> 16) < sslver) {
      failf(data, "CURL_SSLVERSION_MAX incompatible with CURL_SSLVERSION");
      return FALSE;
    }
  }