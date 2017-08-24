{
    size_t i;
    for(i = 0; i < share->max_ssl_sessions; i++)
      Curl_ssl_kill_session(&(share->sslsession[i]));
    free(share->sslsession);
  }