  if(instate == FTP_SIZE) {
#ifdef CURL_FTP_HTTPSTYLE_HEAD
    if(-1 != filesize) {
      char clbuf[128];
      snprintf(clbuf, sizeof(clbuf),
               "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", filesize);
      result = Curl_client_write(conn, CLIENTWRITE_BOTH, clbuf, 0);
      if(result)
        return result;
    }
