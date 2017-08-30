    return AUTH_CONTINUE;
  }

  result = Curl_ftpsendf(conn, "ADAT %s", p);

  free(p);

  if(result)
    return -2;

  if(Curl_GetFTPResponse(&nread, conn, NULL))
    return -1;

  if(data->state.buffer[0] != '2'){
    Curl_failf(data, "Server didn't accept auth data");
