  if(instate == FTP_SIZE) {

#ifdef CURL_FTP_HTTPSTYLE_HEAD

    if(-1 != filesize) {

      snprintf(buf, CURL_BUFSIZE(data->set.buffer_size),

               "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", filesize);

      result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);

      if(result)

