  tmp = Curl_base64_decode(p, &ptr);
  if(tmp >= sizeof(tkt.dat)) {
    free(ptr);
    tmp=0;
  }
  if(!tmp || !ptr) {
    Curl_failf(conn->data, "Failed to decode base64 in reply");
    Curl_set_command_prot(conn, save);
    return CURLE_FTP_WEIRD_SERVER_REPLY;
  }
  memcpy((char *)tkt.dat, ptr, tmp);
  free(ptr);
  tkt.length = tmp;
