{
    CURLcode result;
    result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET, &li->ssldone);
    if(result)
      return result;
  }