CURLcode Curl_SOCKS5(const char *proxy_name,
                     const char *proxy_password,
                     const char *hostname,
                     int remote_port,
                     int sockindex,
                     struct connectdata *conn)
{
  /*
    According to the RFC1928, section "6.  Replies". This is what a SOCK5
    replies:

        +----+-----+-------+------+----------+----------+
        |VER | REP |  RSV  | ATYP | BND.ADDR | BND.PORT |
        +----+-----+-------+------+----------+----------+
        | 1  |  1  | X'00' |  1   | Variable |    2     |
        +----+-----+-------+------+----------+----------+

    Where:

    o  VER    protocol version: X'05'
    o  REP    Reply field:
    o  X'00' succeeded
  */

  unsigned char socksreq[600]; /* room for large user/pw (255 max each) */
  ssize_t actualread;
  ssize_t written;
  int result;
  CURLcode code;
  curl_socket_t sock = conn->sock[sockindex];
  struct SessionHandle *data = conn->data;
  long timeout;
  bool socks5_resolve_local = (bool)(data->set.proxytype == CURLPROXY_SOCKS5);
  const size_t hostname_len = strlen(hostname);
  ssize_t packetsize = 0;

  /* RFC1928 chapter 5 specifies max 255 chars for domain name in packet */
  if(!socks5_resolve_local && hostname_len > 255)
  {
    infof(conn->data,"SOCKS5: server resolving disabled for hostnames of "
          "length > 255 [actual len=%d]\n", hostname_len);
    socks5_resolve_local = TRUE;
  }

  /* get timeout */
  timeout = Curl_timeleft(conn, NULL, TRUE);

  if(timeout < 0) {
    /* time-out, bail out, go home */
    failf(data, "Connection time-out");
    return CURLE_OPERATION_TIMEDOUT;
  }

  Curl_nonblock(sock, TRUE);

  /* wait until socket gets connected */
  result = Curl_socket_ready(CURL_SOCKET_BAD, sock, (int)timeout);

  if(-1 == result) {
    failf(conn->data, "SOCKS5: no connection here");
    return CURLE_COULDNT_CONNECT;
  }
  else if(0 == result) {
    failf(conn->data, "SOCKS5: connection timeout");
    return CURLE_OPERATION_TIMEDOUT;
  }

  if(result & CURL_CSELECT_ERR) {
    failf(conn->data, "SOCKS5: error occured during connection");
    return CURLE_COULDNT_CONNECT;
  }

  socksreq[0] = 5; /* version */
  socksreq[1] = (char)(proxy_name ? 2 : 1); /* number of methods (below) */
  socksreq[2] = 0; /* no authentication */
  socksreq[3] = 2; /* username/password */

  Curl_nonblock(sock, FALSE);

  code = Curl_write(conn, sock, (char *)socksreq, (2 + (int)socksreq[1]),
                      &written);
  if((code != CURLE_OK) || (written != (2 + (int)socksreq[1]))) {
    failf(data, "Unable to send initial SOCKS5 request.");
    return CURLE_COULDNT_CONNECT;
  }

  Curl_nonblock(sock, TRUE);

  result = Curl_socket_ready(sock, CURL_SOCKET_BAD, (int)timeout);

  if(-1 == result) {
    failf(conn->data, "SOCKS5 nothing to read");
    return CURLE_COULDNT_CONNECT;
  }
  else if(0 == result) {
    failf(conn->data, "SOCKS5 read timeout");
    return CURLE_OPERATION_TIMEDOUT;
  }

  if(result & CURL_CSELECT_ERR) {
    failf(conn->data, "SOCKS5 read error occured");
    return CURLE_RECV_ERROR;
  }

  Curl_nonblock(sock, FALSE);

  result=blockread_all(conn, sock, (char *)socksreq, 2, &actualread, timeout);
  if((result != CURLE_OK) || (actualread != 2)) {
    failf(data, "Unable to receive initial SOCKS5 response.");
    return CURLE_COULDNT_CONNECT;
  }

  if(socksreq[0] != 5) {
    failf(data, "Received invalid version in initial SOCKS5 response.");
    return CURLE_COULDNT_CONNECT;
  }
  if(socksreq[1] == 0) {
    /* Nothing to do, no authentication needed */
    ;
  }
  else if(socksreq[1] == 2) {
    /* Needs user name and password */
    size_t userlen, pwlen;
    int len;
    if(proxy_name && proxy_password) {
      userlen = strlen(proxy_name);
      pwlen = strlen(proxy_password);
    }
    else {
      userlen = 0;
      pwlen = 0;
    }

    /*   username/password request looks like
     * +----+------+----------+------+----------+
     * |VER | ULEN |  UNAME   | PLEN |  PASSWD  |
     * +----+------+----------+------+----------+
     * | 1  |  1   | 1 to 255 |  1   | 1 to 255 |
     * +----+------+----------+------+----------+
     */
    len = 0;
    socksreq[len++] = 1;    /* username/pw subnegotiation version */
    socksreq[len++] = (char) userlen;
    memcpy(socksreq + len, proxy_name, (int) userlen);
    len += userlen;
    socksreq[len++] = (char) pwlen;
    memcpy(socksreq + len, proxy_password, (int) pwlen);
    len += pwlen;

    code = Curl_write(conn, sock, (char *)socksreq, len, &written);
    if((code != CURLE_OK) || (len != written)) {
      failf(data, "Failed to send SOCKS5 sub-negotiation request.");
      return CURLE_COULDNT_CONNECT;
    }

    result=blockread_all(conn, sock, (char *)socksreq, 2, &actualread,
                         timeout);
    if((result != CURLE_OK) || (actualread != 2)) {
      failf(data, "Unable to receive SOCKS5 sub-negotiation response.");
      return CURLE_COULDNT_CONNECT;
    }

    /* ignore the first (VER) byte */
    if(socksreq[1] != 0) { /* status */
      failf(data, "User was rejected by the SOCKS5 server (%d %d).",
            socksreq[0], socksreq[1]);
      return CURLE_COULDNT_CONNECT;
    }

    /* Everything is good so far, user was authenticated! */
  }
  else {
    /* error */
    if(socksreq[1] == 1) {
      failf(data,
            "SOCKS5 GSSAPI per-message authentication is not supported.");
      return CURLE_COULDNT_CONNECT;
    }
    else if(socksreq[1] == 255) {
      if(!proxy_name || !*proxy_name) {
        failf(data,
              "No authentication method was acceptable. (It is quite likely"
              " that the SOCKS5 server wanted a username/password, since none"
              " was supplied to the server on this connection.)");
      }
      else {
        failf(data, "No authentication method was acceptable.");
      }
      return CURLE_COULDNT_CONNECT;
    }
    else {
      failf(data,
            "Undocumented SOCKS5 mode attempted to be used by server.");
      return CURLE_COULDNT_CONNECT;
    }
  }

  /* Authentication is complete, now specify destination to the proxy */
  socksreq[0] = 5; /* version (SOCKS5) */
  socksreq[1] = 1; /* connect */
  socksreq[2] = 0; /* must be zero */

  if(!socks5_resolve_local) {
    packetsize = (ssize_t)(5 + hostname_len + 2);

    socksreq[3] = 3; /* ATYP: domain name = 3 */
    socksreq[4] = (char) hostname_len; /* address length */
    memcpy(&socksreq[5], hostname, hostname_len); /* address bytes w/o NULL */

    *((unsigned short*)&socksreq[hostname_len+5]) =
      htons((unsigned short)remote_port);
  }
  else {
    struct Curl_dns_entry *dns;
    Curl_addrinfo *hp=NULL;
    int rc = Curl_resolv(conn, hostname, remote_port, &dns);

    packetsize = 10;

    socksreq[3] = 1; /* IPv4 = 1 */

    if(rc == CURLRESOLV_ERROR)
      return CURLE_COULDNT_RESOLVE_HOST;

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
      failf(data, "Failed to resolve \"%s\" for SOCKS5 connect.",
            hostname);
      return CURLE_COULDNT_RESOLVE_HOST;
    }

    *((unsigned short*)&socksreq[8]) = htons((unsigned short)remote_port);
  }

  code = Curl_write(conn, sock, (char *)socksreq, packetsize, &written);
  if((code != CURLE_OK) || (written != packetsize)) {
    failf(data, "Failed to send SOCKS5 connect request.");
    return CURLE_COULDNT_CONNECT;
  }

  packetsize = 10; /* minimum packet size is 10 */

  result = blockread_all(conn, sock, (char *)socksreq, packetsize,
                           &actualread, timeout);
  if((result != CURLE_OK) || (actualread != packetsize)) {
    failf(data, "Failed to receive SOCKS5 connect request ack.");
    return CURLE_COULDNT_CONNECT;
  }

  if(socksreq[0] != 5) { /* version */
    failf(data,
          "SOCKS5 reply has wrong version, version should be 5.");
    return CURLE_COULDNT_CONNECT;
  }
  if(socksreq[1] != 0) { /* Anything besides 0 is an error */
      failf(data,
            "Can't complete SOCKS5 connection to %d.%d.%d.%d:%d. (%d)",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (unsigned int)ntohs(*(unsigned short*)(&socksreq[8])),
            socksreq[1]);
      return CURLE_COULDNT_CONNECT;
  }

  /* Fix: in general, returned BND.ADDR is variable length parameter by RFC
     1928, so the reply packet should be read until the end to avoid errors at
     subsequent protocol level.

    +----+-----+-------+------+----------+----------+
    |VER | REP |  RSV  | ATYP | BND.ADDR | BND.PORT |
    +----+-----+-------+------+----------+----------+
    | 1  |  1  | X'00' |  1   | Variable |    2     |
    +----+-----+-------+------+----------+----------+

     ATYP:
     o  IP v4 address: X'01', BND.ADDR = 4 byte
     o  domain name:  X'03', BND.ADDR = [ 1 byte length, string ]
     o  IP v6 address: X'04', BND.ADDR = 16 byte
     */

  /* Calculate real packet size */
  if(socksreq[3] == 3) {
    /* domain name */
    int addrlen = (int) socksreq[4];
    packetsize = 5 + addrlen + 2;
  }
  else if(socksreq[3] == 4) {
    /* IPv6 */
    packetsize = 4 + 16 + 2;
  }

  /* At this point we already read first 10 bytes */
  if(packetsize > 10) {
    packetsize -= 10;
    result = blockread_all(conn, sock, (char *)&socksreq[10], packetsize,
                           &actualread, timeout);
    if((result != CURLE_OK) || (actualread != packetsize)) {
      failf(data, "Failed to receive SOCKS5 connect request ack.");
      return CURLE_COULDNT_CONNECT;
    }
  }

  Curl_nonblock(sock, TRUE);
  return CURLE_OK; /* Proxy was successful! */
}