    Curl_failf(conn->data, "Failed to decode base64 in reply.\n");
    Curl_set_command_prot(conn, save);
    return CURLE_FTP_WEIRD_SERVER_REPLY;
  }
  tkt.length = tmp;
  tktcopy.length = tkt.length;

  p = strstr(conn->data->state.buffer, "P=");
  if(!p) {
    Curl_failf(conn->data, "Bad reply from server");
    Curl_set_command_prot(conn, save);
    return CURLE_FTP_WEIRD_SERVER_REPLY;
  }
  name = p + 2;
  for(; *p && *p != ' ' && *p != '\r' && *p != '\n'; p++);
  *p = 0;

  des_string_to_key (conn->passwd, &key);
  des_key_sched(&key, schedule);

  des_pcbc_encrypt((void *)tkt.dat, (void *)tktcopy.dat,
                   tkt.length,
                   schedule, &key, DES_DECRYPT);
  if (strcmp ((char*)tktcopy.dat + 8,
              KRB_TICKET_GRANTING_TICKET) != 0) {
    afs_string_to_key(passwd,
