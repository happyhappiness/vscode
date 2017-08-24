    return AUTH_CONTINUE;
  }

  if(Curl_ftpsendf(conn, "ADAT %s", p))
    return -2;

  nread = Curl_GetFTPResponse(data->state.buffer, conn, NULL);
  if(nread < 0)
    return -1;
  free(p);

  if(data->state.buffer[0] != '2'){
    Curl_failf(data, "Server didn't accept auth data");
