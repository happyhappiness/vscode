static
CURLcode ftp_use_pasv(struct connectdata *conn,
                      bool *connected)
{
  struct SessionHandle *data = conn->data;
  int nread;
  char *buf = data->state.buffer; /* this is our buffer */
  int ftpcode; /* receive FTP response codes in this */
  CURLcode result;
  struct Curl_dns_entry *addr=NULL;
  Curl_ipconnect *conninfo;

  /*
    Here's the excecutive summary on what to do:

    PASV is RFC959, expect:
    227 Entering Passive Mode (a1,a2,a3,a4,p1,p2)

    LPSV is RFC1639, expect:
    228 Entering Long Passive Mode (4,4,a1,a2,a3,a4,2,p1,p2)

    EPSV is RFC2428, expect:
    229 Entering Extended Passive Mode (|||port|)

  */

#if 1
  const char *mode[] = { "EPSV", "PASV", NULL };
  int results[] = { 229, 227, 0 };
#else
#if 0
  char *mode[] = { "EPSV", "LPSV", "PASV", NULL };
  int results[] = { 229, 228, 227, 0 };
#else
  const char *mode[] = { "PASV", NULL };
  int results[] = { 227, 0 };
#endif
#endif
  int modeoff;
  unsigned short connectport; /* the local port connect() should use! */
  unsigned short newport=0; /* remote port, not necessary the local one */
  
  /* newhost must be able to hold a full IP-style address in ASCII, which
     in the IPv6 case means 5*8-1 = 39 letters */
  char newhost[48];
  char *newhostp=NULL;
  
  for (modeoff = (data->set.ftp_use_epsv?0:1);
       mode[modeoff]; modeoff++) {
    result = Curl_ftpsendf(conn, "%s", mode[modeoff]);
    if(result)
      return result;
    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
    if(result)
      return result;
    if (ftpcode == results[modeoff])
      break;
  }

  if (!mode[modeoff]) {
    failf(data, "Odd return code after PASV");
    return CURLE_FTP_WEIRD_PASV_REPLY;
  }
  else if (227 == results[modeoff]) {
    int ip[4];
    int port[2];
    char *str=buf;

    /*
     * New 227-parser June 3rd 1999.
     * It now scans for a sequence of six comma-separated numbers and
     * will take them as IP+port indicators.
     *
     * Found reply-strings include:
     * "227 Entering Passive Mode (127,0,0,1,4,51)"
     * "227 Data transfer will passively listen to 127,0,0,1,4,51"
     * "227 Entering passive mode. 127,0,0,1,4,51"
     */
      
    while(*str) {
      if (6 == sscanf(str, "%d,%d,%d,%d,%d,%d",
                      &ip[0], &ip[1], &ip[2], &ip[3],
                      &port[0], &port[1]))
        break;
      str++;
    }

    if(!*str) {
      failf(data, "Couldn't interpret this 227-reply: %s", buf);
      return CURLE_FTP_WEIRD_227_FORMAT;
    }

    sprintf(newhost, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    newhostp = newhost;
    newport = (unsigned short)((port[0]<<8) + port[1]);
  }
#if 1
  else if (229 == results[modeoff]) {
    char *ptr = strchr(buf, '(');
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
        /* the four separators should be identical */
        newport = (unsigned short)num;

        /* we should use the same host we already are connected to */
        newhostp = conn->name;
      }                      
      else
        ptr=NULL;
    }
    if(!ptr) {
      failf(data, "Weirdly formatted EPSV reply");
      return CURLE_FTP_WEIRD_PASV_REPLY;
    }
  }
#endif
  else
    return CURLE_FTP_CANT_RECONNECT;

  if(data->change.proxy) {
    /*
     * This is a tunnel through a http proxy and we need to connect to the
     * proxy again here.
     *
     * We don't want to rely on a former host lookup that might've expired
     * now, instead we remake the lookup here and now!
     */
    addr = Curl_resolv(data, conn->proxyhost, conn->port);
    connectport =
      (unsigned short)conn->port; /* we connect to the proxy's port */    

  }
  else {
    /* normal, direct, ftp connection */
    addr = Curl_resolv(data, newhostp, newport);
    if(!addr) {
      failf(data, "Can't resolve new host %s:%d", newhostp, newport);
      return CURLE_FTP_CANT_GET_HOST;
    }
    connectport = newport; /* we connect to the remote port */
  }
    
  result = Curl_connecthost(conn,
                            addr,
                            connectport,
                            &conn->secondarysocket,
                            &conninfo,
                            connected);

  Curl_resolv_unlock(addr); /* we're done using this address */

  /*
   * When this is used from the multi interface, this might've returned with
   * the 'connected' set to FALSE and thus we are now awaiting a non-blocking
   * connect to connect and we should not be "hanging" here waiting.
   */
  
  if((CURLE_OK == result) &&       
     data->set.verbose)
    /* this just dumps information about this second connection */
    ftp_pasv_verbose(conn, conninfo, newhostp, connectport);
  
  if(CURLE_OK != result)
    return result;

  if (data->set.tunnel_thru_httpproxy) {
    /* We want "seamless" FTP operations through HTTP proxy tunnel */
    result = Curl_ConnectHTTPProxyTunnel(conn, conn->secondarysocket,
                                         newhostp, newport);
    if(CURLE_OK != result)
      return result;
  }

  return CURLE_OK;
}