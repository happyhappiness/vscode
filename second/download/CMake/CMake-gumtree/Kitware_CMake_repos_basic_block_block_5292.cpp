{
        share->max_ssl_sessions = 8;
        share->sslsession = calloc(share->max_ssl_sessions,
                                   sizeof(struct curl_ssl_session));
        share->sessionage = 0;
        if(!share->sslsession)
          res = CURLSHE_NOMEM;
      }