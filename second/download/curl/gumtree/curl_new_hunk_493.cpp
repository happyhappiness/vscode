    krb4_check_prot,
    krb4_overhead,
    krb4_encode,
    krb4_decode
};

static enum protection_level
krb4_set_command_prot(struct connectdata *conn, enum protection_level level)
{
  enum protection_level old = conn->command_prot;
  DEBUGASSERT(level > PROT_NONE && level < PROT_LAST);
  conn->command_prot = level;
  return old;
}

CURLcode Curl_krb_kauth(struct connectdata *conn)
{
  des_cblock key;
  des_key_schedule schedule;
  KTEXT_ST tkt, tktcopy;
  char *name;
  char *p;
  char passwd[100];
  size_t tmp;
  ssize_t nread;
  enum protection_level save;
  CURLcode result;
  unsigned char *ptr;

  save = krb4_set_command_prot(conn, PROT_PRIVATE);

  result = Curl_ftpsendf(conn, "SITE KAUTH %s", conn->user);

  if(result)
    return result;

  result = Curl_GetFTPResponse(&nread, conn, NULL);
  if(result)
    return result;

  if(conn->data->state.buffer[0] != '3'){
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
  tmp = Curl_base64_decode(p, &ptr);
  if(tmp >= sizeof(tkt.dat)) {
    free(ptr);
    tmp=0;
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

