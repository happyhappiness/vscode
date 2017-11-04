void Curl_krb_kauth(struct connectdata *conn)
{
  des_cblock key;
  des_key_schedule schedule;
  KTEXT_ST tkt, tktcopy;
  char *name;
  char *p;
  char passwd[100];
  int tmp;
  ssize_t nread;
	
  int save;

  save = Curl_set_command_prot(conn, prot_private);

  if(Curl_ftpsendf(conn, "SITE KAUTH %s", conn->data->state.user))
    return;

  nread = Curl_GetFTPResponse(conn->data->state.buffer,
                              conn, NULL);
  if(nread < 0)
    return /*CURLE_OPERATION_TIMEOUTED*/;

  if(conn->data->state.buffer[0] != '3'){
    Curl_set_command_prot(conn, save);
    return;
  }

  p = strstr(conn->data->state.buffer, "T=");
  if(!p) {
    Curl_failf(conn->data, "Bad reply from server");
    Curl_set_command_prot(conn, save);
    return;
  }

  p += 2;
  tmp = Curl_base64_decode(p, &tkt.dat);
  if(tmp < 0) {
    Curl_failf(conn->data, "Failed to decode base64 in reply.\n");
    Curl_set_command_prot(conn, save);
    return;
  }
  tkt.length = tmp;
  tktcopy.length = tkt.length;
    
  p = strstr(conn->data->state.buffer, "P=");
  if(!p) {
    Curl_failf(conn->data, "Bad reply from server");
    Curl_set_command_prot(conn, save);
    return;
  }
  name = p + 2;
  for(; *p && *p != ' ' && *p != '\r' && *p != '\n'; p++);
  *p = 0;

  des_string_to_key (conn->data->state.passwd, &key);
  des_key_sched(&key, schedule);
    
  des_pcbc_encrypt((des_cblock*)tkt.dat, (des_cblock*)tktcopy.dat,
                   tkt.length,
                   schedule, &key, DES_DECRYPT);
  if (strcmp ((char*)tktcopy.dat + 8,
              KRB_TICKET_GRANTING_TICKET) != 0) {
    afs_string_to_key (passwd,
                       krb_realmofhost(conn->hostname),
                       &key);
    des_key_sched (&key, schedule);
    des_pcbc_encrypt((des_cblock*)tkt.dat, (des_cblock*)tktcopy.dat,
                     tkt.length,
                     schedule, &key, DES_DECRYPT);
  }
  memset(key, 0, sizeof(key));
  memset(schedule, 0, sizeof(schedule));
  memset(passwd, 0, sizeof(passwd));
  if(Curl_base64_encode(tktcopy.dat, tktcopy.length, &p) < 0) {
    failf(conn->data, "Out of memory base64-encoding.");
    Curl_set_command_prot(conn, save);
    return;
  }
  memset (tktcopy.dat, 0, tktcopy.length);

  if(Curl_ftpsendf(conn, "SITE KAUTH %s %s", name, p))
    return;

  nread = Curl_GetFTPResponse(conn->data->state.buffer,
                              conn, NULL);
  if(nread < 0)
    return /*CURLE_OPERATION_TIMEOUTED*/;
  free(p);
  Curl_set_command_prot(conn, save);
}