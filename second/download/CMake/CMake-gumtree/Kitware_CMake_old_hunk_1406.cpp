  if(!p) {
    Curl_failf(conn->data, "Bad reply from server");
    Curl_set_command_prot(conn, save);
    return;
  }
  name = p + 2;
  for(; *p && *p != ' ' && *p != '\r' && *p != '\n'; p++);
