  int len;
  KTEXT_ST adat;
  MSG_DAT msg_data;
  int checksum;
  u_int32_t cs;
  struct krb4_data *d = app_data;
  struct sockaddr_in *localaddr  = (struct sockaddr_in *)LOCAL_ADDR;
  char *host = conn->hp->h_name;
  ssize_t nread;
  int l = sizeof(conn->local_addr);

  if(getsockname(conn->firstsocket,
                 (struct sockaddr *)LOCAL_ADDR, &l) < 0)
    perror("getsockname()");

  checksum = getpid();
  ret = mk_auth(d, &adat, "ftp", host, checksum);
  if(ret == KDC_PR_UNKNOWN)
    ret = mk_auth(d, &adat, "rcmd", host, checksum);
  if(ret) {
    printf("%s\n", krb_get_err_text(ret));
    return AUTH_CONTINUE;
  }
  
#ifdef HAVE_KRB_GET_OUR_IP_FOR_REALM
  if (krb_get_config_bool("nat_in_use")) {
    struct in_addr natAddr;

    if (krb_get_our_ip_for_realm(krb_realmofhost(host),
                                 &natAddr) != KSUCCESS
        && krb_get_our_ip_for_realm(NULL, &natAddr) != KSUCCESS)
      printf("Can't get address for realm %s\n",
             krb_realmofhost(host));
    else {
      if (natAddr.s_addr != localaddr->sin_addr.s_addr) {
        printf("Using NAT IP address (%s) for kerberos 4\n",
               (char *)inet_ntoa(natAddr));
        localaddr->sin_addr = natAddr;
        
        /*
         * This not the best place to do this, but it is here we know that
         * (probably) NAT is in use!  */

        /*passivemode = 1;***/
        /*printf("Setting: Passive mode on.\n");***/
      }
    }
  }
#endif

  /*printf("Local address is %s\n", inet_ntoa(localaddr->sin_addr));***/
  /*printf("Remote address is %s\n", inet_ntoa(remoteaddr->sin_addr));***/

  if(Curl_base64_encode(adat.dat, adat.length, &p) < 0) {
    printf("Out of memory base64-encoding.\n");
    return AUTH_CONTINUE;
  }

  Curl_ftpsendf(conn->firstsocket, conn, "ADAT %s", p);

  nread = Curl_GetFTPResponse(conn->firstsocket,
                              conn->data->state.buffer, conn, NULL);
  if(nread < 0)
    return /*CURLE_OPERATION_TIMEOUTED*/-1;
  free(p);

  if(/*ret != COMPLETE*/conn->data->state.buffer[0] != '2'){
    printf("Server didn't accept auth data.\n");
    return AUTH_ERROR;
  }

  p = strstr(conn->data->state.buffer, "ADAT=");
  if(!p){
    printf("Remote host didn't send adat reply.\n");
    return AUTH_ERROR;
  }
  p += 5;
  len = Curl_base64_decode(p, adat.dat);
  if(len < 0){
    printf("Failed to decode base64 from server.\n");
    return AUTH_ERROR;
  }
  adat.length = len;
  ret = krb_rd_safe(adat.dat, adat.length, &d->key, 
                    (struct sockaddr_in *)hisctladdr, 
                    (struct sockaddr_in *)myctladdr, &msg_data);
  if(ret){
    printf("Error reading reply from server: %s.\n", 
           krb_get_err_text(ret));
    return AUTH_ERROR;
  }
  krb_get_int(msg_data.app_data, &cs, 4, 0);
  if(cs - checksum != 1){
    printf("Bad checksum returned from server.\n");
    return AUTH_ERROR;
  }
  return AUTH_OK;
}

struct Curl_sec_client_mech Curl_krb4_client_mech = {
