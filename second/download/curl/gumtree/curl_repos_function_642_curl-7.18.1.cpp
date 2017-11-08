CURLcode Curl_SOCKS4(const char *proxy_name,
                     const char *hostname,
                     int remote_port,
                     int sockindex,
                     struct connectdata *conn,
                     bool protocol4a)
{
#define SOCKS4REQLEN 262
  unsigned char socksreq[SOCKS4REQLEN]; /* room for SOCKS4 request incl. user
                                           id */
  int result;
  CURLcode code;
  curl_socket_t sock = conn->sock[sockindex];
  long timeout;
  struct SessionHandle *data = conn->data;

  /* get timeout */
  timeout = Curl_timeleft(conn, NULL, TRUE);

  if(timeout < 0) {
    /* time-out, bail out, go home */
    failf(data, "Connection time-out");
    return CURLE_OPERATION_TIMEDOUT;
  }

  Curl_nonblock(sock, FALSE);

  /*
   * Compose socks4 request
   *
   * Request format
   *
   *     +----+----+----+----+----+----+----+----+----+----+....+----+
   *     | VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
   *     +----+----+----+----+----+----+----+----+----+----+....+----+
   * # of bytes:  1    1      2              4           variable       1
   */

  socksreq[0] = 4; /* version (SOCKS4) */
  socksreq[1] = 1; /* connect */
  *((unsigned short*)&socksreq[2]) = htons((unsigned short)remote_port);

  /* DNS resolve only for SOCKS4, not SOCKS4a */
  if (!protocol4a) {
    struct Curl_dns_entry *dns;
    Curl_addrinfo *hp=NULL;
    int rc;

    rc = Curl_resolv(conn, hostname, remote_port, &dns);

    if(rc == CURLRESOLV_ERROR)
      return CURLE_COULDNT_RESOLVE_PROXY;

    if(rc == CURLRESOLV_PENDING)
      /* this requires that we're in "wait for resolve" state */
      rc = Curl_wait_for_resolv(conn, &dns);

    /*
     * We cannot use 'hostent' as a struct that Curl_resolv() returns.  It
     * returns a Curl_addrinfo pointer that may not always look the same.
     */
    if(dns)
      hp=dns->addr;
    if(hp) {
      char buf[64];
      unsigned short ip[4];
      Curl_printable_address(hp, buf, sizeof(buf));

      if(4 == sscanf( buf, "%hu.%hu.%hu.%hu",
                      &ip[0], &ip[1], &ip[2], &ip[3])) {
        /* Set DSTIP */
        socksreq[4] = (unsigned char)ip[0];
        socksreq[5] = (unsigned char)ip[1];
        socksreq[6] = (unsigned char)ip[2];
        socksreq[7] = (unsigned char)ip[3];
      }
      else
        hp = NULL; /* fail! */

      Curl_resolv_unlock(data, dns); /* not used anymore from now on */

    }
    if(!hp) {
      failf(data, "Failed to resolve \"%s\" for SOCKS4 connect.",
            hostname);
      return CURLE_COULDNT_RESOLVE_HOST;
    }
  }

  /*
   * This is currently not supporting "Identification Protocol (RFC1413)".
   */
  socksreq[8] = 0; /* ensure empty userid is NUL-terminated */
  if(proxy_name)
    strlcat((char*)socksreq + 8, proxy_name, sizeof(socksreq) - 8);

  /*
   * Make connection
   */
  {
    ssize_t actualread;
    ssize_t written;
    ssize_t hostnamelen = 0;
    int packetsize = 9 +
      (int)strlen((char*)socksreq + 8); /* size including NUL */

    /* If SOCKS4a, set special invalid IP address 0.0.0.x */
    if (protocol4a) {
      socksreq[4] = 0;
      socksreq[5] = 0;
      socksreq[6] = 0;
      socksreq[7] = 1;
      /* If still enough room in buffer, also append hostname */
      hostnamelen = (ssize_t)strlen(hostname) + 1; /* length including NUL */
      if (packetsize + hostnamelen <= SOCKS4REQLEN)
        strcpy((char*)socksreq + packetsize, hostname);
      else
        hostnamelen = 0; /* Flag: hostname did not fit in buffer */
    }

    /* Send request */
    code = Curl_write(conn, sock, (char *)socksreq, packetsize + hostnamelen,
                      &written);
    if((code != CURLE_OK) || (written != packetsize + hostnamelen)) {
      failf(data, "Failed to send SOCKS4 connect request.");
      return CURLE_COULDNT_CONNECT;
    }
    if (protocol4a && hostnamelen == 0) {
      /* SOCKS4a with very long hostname - send that name separately */
      hostnamelen = (ssize_t)strlen(hostname) + 1;
      code = Curl_write(conn, sock, (char *)hostname, hostnamelen, &written);
      if((code != CURLE_OK) || (written != hostnamelen)) {
        failf(data, "Failed to send SOCKS4 connect request.");
        return CURLE_COULDNT_CONNECT;
      }
    }

    packetsize = 8; /* receive data size */

    /* Receive response */
    result = blockread_all(conn, sock, (char *)socksreq, packetsize,
                           &actualread, timeout);
    if((result != CURLE_OK) || (actualread != packetsize)) {
      failf(data, "Failed to receive SOCKS4 connect request ack.");
      return CURLE_COULDNT_CONNECT;
    }

    /*
     * Response format
     *
     *     +----+----+----+----+----+----+----+----+
     *     | VN | CD | DSTPORT |      DSTIP        |
     *     +----+----+----+----+----+----+----+----+
     * # of bytes:  1    1      2              4
     *
     * VN is the version of the reply code and should be 0. CD is the result
     * code with one of the following values:
     *
     * 90: request granted
     * 91: request rejected or failed
     * 92: request rejected because SOCKS server cannot connect to
     *     identd on the client
     * 93: request rejected because the client program and identd
     *     report different user-ids
     */

    /* wrong version ? */
    if(socksreq[0] != 0) {
      failf(data,
            "SOCKS4 reply has wrong version, version should be 4.");
      return CURLE_COULDNT_CONNECT;
    }

    /* Result */
    switch(socksreq[1])
    {
    case 90:
      if (protocol4a)
        infof(data, "SOCKS4a request granted.\n");
      else
        infof(data, "SOCKS4 request granted.\n");
      break;
    case 91:
      failf(data,
            "Can't complete SOCKS4 connection to %d.%d.%d.%d:%d. (%d)"
            ", request rejected or failed.",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (unsigned int)ntohs(*(unsigned short*)(&socksreq[8])),
            socksreq[1]);
      return CURLE_COULDNT_CONNECT;
    case 92:
      failf(data,
            "Can't complete SOCKS4 connection to %d.%d.%d.%d:%d. (%d)"
            ", request rejected because SOCKS server cannot connect to "
            "identd on the client.",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (unsigned int)ntohs(*(unsigned short*)(&socksreq[8])),
            socksreq[1]);
      return CURLE_COULDNT_CONNECT;
    case 93:
      failf(data,
            "Can't complete SOCKS4 connection to %d.%d.%d.%d:%d. (%d)"
            ", request rejected because the client program and identd "
            "report different user-ids.",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (unsigned int)ntohs(*(unsigned short*)(&socksreq[8])),
            socksreq[1]);
      return CURLE_COULDNT_CONNECT;
    default:
      failf(data,
            "Can't complete SOCKS4 connection to %d.%d.%d.%d:%d. (%d)"
            ", Unknown.",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (unsigned int)ntohs(*(unsigned short*)(&socksreq[8])),
            socksreq[1]);
      return CURLE_COULDNT_CONNECT;
    }
  }

  Curl_nonblock(sock, TRUE);

  return CURLE_OK; /* Proxy was successful! */
}