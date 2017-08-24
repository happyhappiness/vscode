{
    Curl_ssl_sessionid_lock(conn);
    Curl_schannel_session_free(connssl->cred);
    Curl_ssl_sessionid_unlock(conn);
    connssl->cred = NULL;
  }