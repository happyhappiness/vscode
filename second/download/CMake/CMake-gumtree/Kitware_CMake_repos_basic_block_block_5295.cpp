{
    case CURL_LOCK_DATA_DNS:
      break;

    case CURL_LOCK_DATA_COOKIE:
#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
      if(!share->cookies) {
        share->cookies = Curl_cookie_init(NULL, NULL, NULL, TRUE);
        if(!share->cookies)
          res = CURLSHE_NOMEM;
      }
#else   /* CURL_DISABLE_HTTP */
      res = CURLSHE_NOT_BUILT_IN;
#endif
      break;

    case CURL_LOCK_DATA_SSL_SESSION:
#ifdef USE_SSL
      if(!share->sslsession) {
        share->max_ssl_sessions = 8;
        share->sslsession = calloc(share->max_ssl_sessions,
                                   sizeof(struct curl_ssl_session));
        share->sessionage = 0;
        if(!share->sslsession)
          res = CURLSHE_NOMEM;
      }
#else
      res = CURLSHE_NOT_BUILT_IN;
#endif
      break;

    case CURL_LOCK_DATA_CONNECT:     /* not supported (yet) */
      break;

    default:
      res = CURLSHE_BAD_OPTION;
    }