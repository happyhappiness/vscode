CURLcode Curl_krb_kauth(struct connectdata *conn)
{
  des_cblock key;
  des_key_schedule schedule;
  KTEXT_ST tkt, tktcopy;
  char *name;
  char *p;
  char passwd[100];
  size_t tmp = 0;
  ssize_t nread;
  enum protection_level save;
  CURLcode result;
  unsigned char *ptr;
  size_t base64_sz = 0;

  save = krb4_set_command_prot(conn, PROT_PRIVATE);

  result = Curl_ftpsendf(conn, "SITE KAUTH %s", conn->user);

  if(result)
    return result;

  result = Curl_GetFTPResponse(&nread, conn, NULL);
  if(result)
    return result;

  if(conn->data->state.buffer[0] != '3') {
    krb4_set_command_prot(conn, save);
    return CURLE_FTP_WEIRD_SERVER_REPLY;
  }

  p = strstr(conn->data->state.buffer, "T=");
  if(!p) {
    Curl_failf(conn->data, "Bad reply from server");
    krb4_set_command_prot(conn, save);
    return CURLE_FTP_WEIRD_SERVER_REPLY;
  }

  p += 2;
  result = Curl_base64_decode(p, &ptr, &tmp);
  if(result) {
    Curl_failf(conn->data, "base64-decoding: %s", curl_easy_strerror(result));
    return result;
  }
  if(tmp >= sizeof(tkt.dat)) {
    free(ptr);
    ptr = NULL;
    tmp = 0;
  }
  if(!tmp || !ptr) {
    Curl_failf(conn->data, "Failed to decode base64 in reply");
    krb4_set_command_prot(conn, save);
    return CURLE_FTP_WEIRD_SERVER_REPLY;
  }
  memcpy((char *)tkt.dat, ptr, tmp);
  free(ptr);
  tkt.length = tmp;
  tktcopy.length = tkt.length;

  p = strstr(conn->data->state.buffer, "P=");
  if(!p) {
    Curl_failf(conn->data, "Bad reply from server");
    krb4_set_command_prot(conn, save);
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
  if(strcmp ((char*)tktcopy.dat + 8,
              KRB_TICKET_GRANTING_TICKET) != 0) {
    afs_string_to_key(passwd,
                      krb_realmofhost(conn->host.name),
                      &key);
    des_key_sched(&key, schedule);
    des_pcbc_encrypt((void *)tkt.dat, (void *)tktcopy.dat,
                     tkt.length,
                     schedule, &key, DES_DECRYPT);
  }
  memset(key, 0, sizeof(key));
  memset(schedule, 0, sizeof(schedule));
  memset(passwd, 0, sizeof(passwd));
  result = Curl_base64_encode(conn->data, (char *)tktcopy.dat, tktcopy.length,
                              &p, &base64_sz);
  if(result) {
    Curl_failf(conn->data, "base64-encoding: %s", curl_easy_strerror(result));
    krb4_set_command_prot(conn, save);
    return result;
  }
  memset (tktcopy.dat, 0, tktcopy.length);

  result = Curl_ftpsendf(conn, "SITE KAUTH %s %s", name, p);
  free(p);
  if(result)
    return result;

  result = Curl_GetFTPResponse(&nread, conn, NULL);
  if(result)
    return result;
  krb4_set_command_prot(conn, save);

  return CURLE_OK;
}