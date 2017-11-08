static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
                                    int ftpcode)
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  CURLcode result;
  struct SessionHandle *data=conn->data;
  Curl_addrinfo *conninfo;
  struct Curl_dns_entry *addr=NULL;
  int rc;
  unsigned short connectport; /* the local port connect() should use! */
  unsigned short newport=0; /* remote port */
  bool connected;

  /* newhost must be able to hold a full IP-style address in ASCII, which
     in the IPv6 case means 5*8-1 = 39 letters */
#define NEWHOST_BUFSIZE 48
  char newhost[NEWHOST_BUFSIZE];
  char *str=&data->state.buffer[4];  /* start on the first letter */

  if((ftpc->count1 == 0) &&
     (ftpcode == 229)) {
    /* positive EPSV response */
    char *ptr = strchr(str, '(');
    if(ptr) {
      unsigned int num;
      char separator[4];
      ptr++;
      if(5  == sscanf(ptr, "%c%c%c%u%c",
                      &separator[0],
                      &separator[1],
                      &separator[2],
                      &num,
                      &separator[3])) {
        const char sep1 = separator[0];
        int i;

        /* The four separators should be identical, or else this is an oddly
           formatted reply and we bail out immediately. */
        for(i=1; i<4; i++) {
          if(separator[i] != sep1) {
            ptr=NULL; /* set to NULL to signal error */
            break;
          }
        }
        if(ptr) {
          newport = (unsigned short)(num & 0xffff);

          if(conn->bits.tunnel_proxy ||
             data->set.proxytype == CURLPROXY_SOCKS5 ||
             data->set.proxytype == CURLPROXY_SOCKS5_HOSTNAME ||
             data->set.proxytype == CURLPROXY_SOCKS4 ||
             data->set.proxytype == CURLPROXY_SOCKS4A)
            /* proxy tunnel -> use other host info because ip_addr_str is the
               proxy address not the ftp host */
            snprintf(newhost, sizeof(newhost), "%s", conn->host.name);
          else
            /* use the same IP we are already connected to */
            snprintf(newhost, NEWHOST_BUFSIZE, "%s", conn->ip_addr_str);
        }
      }
      else
        ptr=NULL;
    }
    if(!ptr) {
      failf(data, "Weirdly formatted EPSV reply");
      return CURLE_FTP_WEIRD_PASV_REPLY;
    }
  }
  else if((ftpc->count1 == 1) &&
          (ftpcode == 227)) {
    /* positive PASV response */
    int ip[4];
    int port[2];

    /*
     * Scan for a sequence of six comma-separated numbers and use them as
     * IP+port indicators.
     *
     * Found reply-strings include:
     * "227 Entering Passive Mode (127,0,0,1,4,51)"
     * "227 Data transfer will passively listen to 127,0,0,1,4,51"
     * "227 Entering passive mode. 127,0,0,1,4,51"
     */
    while(*str) {
      if(6 == sscanf(str, "%d,%d,%d,%d,%d,%d",
                      &ip[0], &ip[1], &ip[2], &ip[3],
                      &port[0], &port[1]))
        break;
      str++;
    }

    if(!*str) {
      failf(data, "Couldn't interpret the 227-response");
      return CURLE_FTP_WEIRD_227_FORMAT;
    }

    /* we got OK from server */
    if(data->set.ftp_skip_ip) {
      /* told to ignore the remotely given IP but instead use the one we used
         for the control connection */
      infof(data, "Skips %d.%d.%d.%d for data connection, uses %s instead\n",
            ip[0], ip[1], ip[2], ip[3],
            conn->ip_addr_str);
      if(conn->bits.tunnel_proxy ||
          data->set.proxytype == CURLPROXY_SOCKS5 ||
          data->set.proxytype == CURLPROXY_SOCKS5_HOSTNAME ||
          data->set.proxytype == CURLPROXY_SOCKS4 ||
          data->set.proxytype == CURLPROXY_SOCKS4A)
        /* proxy tunnel -> use other host info because ip_addr_str is the
           proxy address not the ftp host */
        snprintf(newhost, sizeof(newhost), "%s", conn->host.name);
      else
        snprintf(newhost, sizeof(newhost), "%s", conn->ip_addr_str);
    }
    else
      snprintf(newhost, sizeof(newhost),
               "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    newport = (unsigned short)(((port[0]<<8) + port[1]) & 0xffff);
  }
  else if(ftpc->count1 == 0) {
    /* EPSV failed, move on to PASV */

    /* disable it for next transfer */
    conn->bits.ftp_use_epsv = FALSE;
    infof(data, "disabling EPSV usage\n");

    NBFTPSENDF(conn, "PASV", NULL);
    ftpc->count1++;
    /* remain in the FTP_PASV state */
    return result;
  }
  else {
    failf(data, "Bad PASV/EPSV response: %03d", ftpcode);
    return CURLE_FTP_WEIRD_PASV_REPLY;
  }

  if(data->set.str[STRING_PROXY] && *data->set.str[STRING_PROXY]) {
    /*
     * This is a tunnel through a http proxy and we need to connect to the
     * proxy again here.
     *
     * We don't want to rely on a former host lookup that might've expired
     * now, instead we remake the lookup here and now!
     */
    rc = Curl_resolv(conn, conn->proxy.name, (int)conn->port, &addr);
    if(rc == CURLRESOLV_PENDING)
      /* BLOCKING */
      rc = Curl_wait_for_resolv(conn, &addr);

    connectport =
      (unsigned short)conn->port; /* we connect to the proxy's port */

  }
  else {
    /* normal, direct, ftp connection */
    rc = Curl_resolv(conn, newhost, newport, &addr);
    if(rc == CURLRESOLV_PENDING)
      /* BLOCKING */
      rc = Curl_wait_for_resolv(conn, &addr);

    if(!addr) {
      failf(data, "Can't resolve new host %s:%d", newhost, newport);
      return CURLE_FTP_CANT_GET_HOST;
    }
    connectport = newport; /* we connect to the remote port */
  }

  result = Curl_connecthost(conn,
                            addr,
                            &conn->sock[SECONDARYSOCKET],
                            &conninfo,
                            &connected);

  Curl_resolv_unlock(data, addr); /* we're done using this address */

  if(result && ftpc->count1 == 0 && ftpcode == 229) {
    infof(data, "got positive EPSV response, but can't connect. "
          "Disabling EPSV\n");
    /* disable it for next transfer */
    conn->bits.ftp_use_epsv = FALSE;
    data->state.errorbuf = FALSE; /* allow error message to get rewritten */
    NBFTPSENDF(conn, "PASV", NULL);
    ftpc->count1++;
    /* remain in the FTP_PASV state */
    return result;
 }

  if(result)
    return result;

  conn->bits.tcpconnect = connected; /* simply TRUE or FALSE */

  /*
   * When this is used from the multi interface, this might've returned with
   * the 'connected' set to FALSE and thus we are now awaiting a non-blocking
   * connect to connect and we should not be "hanging" here waiting.
   */

  if(data->set.verbose)
    /* this just dumps information about this second connection */
    ftp_pasv_verbose(conn, conninfo, newhost, connectport);

  switch(data->set.proxytype) {
  case CURLPROXY_SOCKS5:
  case CURLPROXY_SOCKS5_HOSTNAME:
    result = Curl_SOCKS5(conn->proxyuser, conn->proxypasswd, newhost, newport,
                         SECONDARYSOCKET, conn);
    break;
  case CURLPROXY_HTTP:
    /* do nothing here. handled later. */
    break;
  case CURLPROXY_SOCKS4:
    result = Curl_SOCKS4(conn->proxyuser, newhost, newport,
                         SECONDARYSOCKET, conn, FALSE);
    break;
  case CURLPROXY_SOCKS4A:
    result = Curl_SOCKS4(conn->proxyuser, newhost, newport,
                         SECONDARYSOCKET, conn, TRUE);
    break;
  default:
    failf(data, "unknown proxytype option given");
    result = CURLE_COULDNT_CONNECT;
    break;
  }
#ifndef CURL_DISABLE_HTTP
  if(conn->bits.tunnel_proxy && conn->bits.httpproxy) {
    /* FIX: this MUST wait for a proper connect first if 'connected' is
     * FALSE */

    /* BLOCKING */
    /* We want "seamless" FTP operations through HTTP proxy tunnel */

    /* Curl_proxyCONNECT is based on a pointer to a struct HTTP at the member
     * conn->proto.http; we want FTP through HTTP and we have to change the
     * member temporarily for connecting to the HTTP proxy. After
     * Curl_proxyCONNECT we have to set back the member to the original struct
     * FTP pointer
     */
    struct HTTP http_proxy;
    struct FTP *ftp_save = data->state.proto.ftp;
    memset(&http_proxy, 0, sizeof(http_proxy));
    data->state.proto.http = &http_proxy;

    result = Curl_proxyCONNECT(conn, SECONDARYSOCKET, newhost, newport);

    data->state.proto.ftp = ftp_save;

    if(CURLE_OK != result)
      return result;
  }
#endif   /* CURL_DISABLE_HTTP */

  state(conn, FTP_STOP); /* this phase is completed */

  return result;
}