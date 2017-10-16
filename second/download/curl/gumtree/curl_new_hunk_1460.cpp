  int len;
  KTEXT_ST adat;
  MSG_DAT msg_data;
  int checksum;
  u_int32_t cs;
  struct krb4_data *d = app_data;
  char *host = conn->hostname;
  ssize_t nread;
  int l = sizeof(conn->local_addr);
  struct SessionHandle *data = conn->data;

  if(getsockname(conn->firstsocket,
                 (struct sockaddr *)LOCAL_ADDR, &l) < 0)
    perror("getsockname()");

  checksum = getpid();
  ret = mk_auth(d, &adat, "ftp", host, checksum);
  if(ret == KDC_PR_UNKNOWN)
    ret = mk_auth(d, &adat, "rcmd", host, checksum);
  if(ret) {
    Curl_infof(data, "%s\n", krb_get_err_text(ret));
    return AUTH_CONTINUE;
  }
  
#ifdef HAVE_KRB_GET_OUR_IP_FOR_REALM
  if (krb_get_config_bool("nat_in_use")) {
    struct sockaddr_in *localaddr  = (struct sockaddr_in *)LOCAL_ADDR;
    struct in_addr natAddr;

    if (krb_get_our_ip_for_realm(krb_realmofhost(host),
                                 &natAddr) != KSUCCESS
        && krb_get_our_ip_for_realm(NULL, &natAddr) != KSUCCESS)
      Curl_infof(data, "Can't get address for realm %s\n",
                 krb_realmofhost(host));
    else {
      if (natAddr.s_addr != localaddr->sin_addr.s_addr) {
#ifdef HAVE_INET_NTOA_R
        char ntoa_buf[64];
        char *ip = (char *)inet_ntoa_r(natAddr, ntoa_buf, sizeof(ntoa_buf));
#else
        char *ip = (char *)inet_ntoa(natAddr);
#endif
        Curl_infof(data, "Using NAT IP address (%s) for kerberos 4\n", ip);
        localaddr->sin_addr = natAddr;
      }
    }
  }
#endif

  if(Curl_base64_encode(adat.dat, adat.length, &p) < 0) {
    Curl_failf(data, "Out of memory base64-encoding");
    return AUTH_CONTINUE;
  }

  if(Curl_ftpsendf(conn, "ADAT %s", p))
    return -2;

  nread = Curl_GetFTPResponse(data->state.buffer, conn, NULL);
  if(nread < 0)
    return -1;
  free(p);

  if(data->state.buffer[0] != '2'){
    Curl_failf(data, "Server didn't accept auth data");
    return AUTH_ERROR;
  }

  p = strstr(data->state.buffer, "ADAT=");
  if(!p) {
    Curl_failf(data, "Remote host didn't send adat reply");
    return AUTH_ERROR;
  }
  p += 5;
  len = Curl_base64_decode(p, adat.dat);
  if(len < 0) {
    Curl_failf(data, "Failed to decode base64 from server");
    return AUTH_ERROR;
  }
  adat.length = len;
  ret = krb_rd_safe(adat.dat, adat.length, &d->key, 
                    (struct sockaddr_in *)hisctladdr, 
                    (struct sockaddr_in *)myctladdr, &msg_data);
  if(ret) {
    Curl_failf(data, "Error reading reply from server: %s", 
               krb_get_err_text(ret));
    return AUTH_ERROR;
  }
  krb_get_int(msg_data.app_data, &cs, 4, 0);
  if(cs - checksum != 1) {
    Curl_failf(data, "Bad checksum returned from server");
    return AUTH_ERROR;
  }
  return AUTH_OK;
}

struct Curl_sec_client_mech Curl_krb4_client_mech = {
