  if(result)
    return -2;

  if(Curl_GetFTPResponse(&nread, conn, NULL))
    return -1;

  if(data->state.buffer[0] != '2'){
    Curl_failf(data, "Server didn't accept auth data");
    return AUTH_ERROR;
  }

  p = strstr(data->state.buffer, "ADAT=");
  if(!p) {
    Curl_failf(data, "Remote host didn't send adat reply");
    return AUTH_ERROR;
  }
  p += 5;
  len = Curl_base64_decode(p, &ptr);
  if(len > sizeof(adat.dat)-1) {
    free(ptr);
    len=0;
  }
  if(!len || !ptr) {
    Curl_failf(data, "Failed to decode base64 from server");
    return AUTH_ERROR;
  }
  memcpy((char *)adat.dat, ptr, len);
