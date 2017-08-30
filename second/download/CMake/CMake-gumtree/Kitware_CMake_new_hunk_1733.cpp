  if(!p) {

    Curl_failf(conn->data, "Bad reply from server");

    Curl_set_command_prot(conn, save);

    return CURLE_FTP_WEIRD_SERVER_REPLY;

  }

  name = p + 2;

  for(; *p && *p != ' ' && *p != '\r' && *p != '\n'; p++);

