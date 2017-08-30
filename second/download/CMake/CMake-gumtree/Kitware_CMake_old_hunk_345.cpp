  vsnprintf(print_buffer, sizeof(print_buffer), message, args);

  va_end(args);



  if(Curl_ftpsendf(conn, print_buffer)) {

    ftp_code = -1;

  }

  else {

