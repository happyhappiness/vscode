static int handleSock5Proxy(const char *proxy_name,
                            const char *proxy_password,
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
  curl_socket_t sock = conn->sock[FIRSTSOCKET];

  Curl_nonblock(sock, FALSE);

  socksreq[0] = 5; /* version */
  socksreq[1] = (char)(proxy_name ? 2 : 1); /* number of methods (below) */
  socksreq[2] = 0; /* no authentication */
  socksreq[3] = 2; /* username/password */

  code = Curl_write(conn, sock, (char *)socksreq, (2 + (int)socksreq[1]),
                      &written);
  if ((code != CURLE_OK) || (written != (2 + (int)socksreq[1]))) {
    failf(conn->data, "Unable to send initial SOCKS5 request.");
    return 1;
  }

  result=Curl_read(conn, sock, (char *)socksreq, 2, &actualread);
  if ((result != CURLE_OK) || (actualread != 2)) {
    failf(conn->data, "Unable to receive initial SOCKS5 response.");
    return 1;
  }

  if (socksreq[0] != 5) {
    failf(conn->data, "Received invalid version in initial SOCKS5 response.");
    return 1;
  }
  if (socksreq[1] == 0) {
    /* Nothing to do, no authentication needed */
    ;
  }
  else if (socksreq[1] == 2) {
    /* Needs user name and password */
    int userlen, pwlen, len;

    userlen = (int)strlen(proxy_name);
    pwlen = proxy_password?(int)strlen(proxy_password):0;

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
    if ((code != CURLE_OK) || (len != written)) {
      failf(conn->data, "Failed to send SOCKS5 sub-negotiation request.");
      return 1;
    }

    result=Curl_read(conn, sock, (char *)socksreq, 2, &actualread);
    if ((result != CURLE_OK) || (actualread != 2)) {
      failf(conn->data, "Unable to receive SOCKS5 sub-negotiation response.");
      return 1;
    }

    /* ignore the first (VER) byte */
    if (socksreq[1] != 0) { /* status */
      failf(conn->data, "User was rejected by the SOCKS5 server (%d %d).",
            socksreq[0], socksreq[1]);
      return 1;
    }

    /* Everything is good so far, user was authenticated! */
  }
  else {
    /* error */
    if (socksreq[1] == 1) {
      failf(conn->data,
            "SOCKS5 GSSAPI per-message authentication is not supported.");
      return 1;
    }
    else if (socksreq[1] == 255) {
      if (!proxy_name || !*proxy_name) {
        failf(conn->data,
              "No authentication method was acceptable. (It is quite likely"
              " that the SOCKS5 server wanted a username/password, since none"
              " was supplied to the server on this connection.)");
      }
      else {
        failf(conn->data, "No authentication method was acceptable.");
      }
      return 1;
    }
    else {
      failf(conn->data,
            "Undocumented SOCKS5 mode attempted to be used by server.");
      return 1;
    }
  }

  /* Authentication is complete, now specify destination to the proxy */
  socksreq[0] = 5; /* version (SOCKS5) */
  socksreq[1] = 1; /* connect */
  socksreq[2] = 0; /* must be zero */
  socksreq[3] = 1; /* IPv4 = 1 */

  {
    struct Curl_dns_entry *dns;
    Curl_addrinfo *hp=NULL;
    int rc = Curl_resolv(conn, conn->host.name, (int)conn->remote_port, &dns);

    if(rc == CURLRESOLV_ERROR)
      return 1;

    if(rc == CURLRESOLV_PENDING)
      /* this requires that we're in "wait for resolve" state */
      rc = Curl_wait_for_resolv(conn, &dns);

    /*
     * We cannot use 'hostent' as a struct that Curl_resolv() returns.  It
     * returns a Curl_addrinfo pointer that may not always look the same.
     */
    if(dns)
      hp=dns->addr;
    if (hp) {
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

      Curl_resolv_unlock(conn->data, dns); /* not used anymore from now on */
    }
    if(!hp) {
      failf(conn->data, "Failed to resolve \"%s\" for SOCKS5 connect.",
            conn->host.name);
      return 1;
    }
  }

  *((unsigned short*)&socksreq[8]) = htons(conn->remote_port);

  {
    const int packetsize = 10;

    code = Curl_write(conn, sock, (char *)socksreq, packetsize, &written);
    if ((code != CURLE_OK) || (written != packetsize)) {
      failf(conn->data, "Failed to send SOCKS5 connect request.");
      return 1;
    }

    result = Curl_read(conn, sock, (char *)socksreq, packetsize, &actualread);
    if ((result != CURLE_OK) || (actualread != packetsize)) {
      failf(conn->data, "Failed to receive SOCKS5 connect request ack.");
      return 1;
    }

    if (socksreq[0] != 5) { /* version */
      failf(conn->data,
            "SOCKS5 reply has wrong version, version should be 5.");
      return 1;
    }
    if (socksreq[1] != 0) { /* Anything besides 0 is an error */
        failf(conn->data,
              "Can't complete SOCKS5 connection to %d.%d.%d.%d:%d. (%d)",
              (unsigned char)socksreq[4], (unsigned char)socksreq[5],
              (unsigned char)socksreq[6], (unsigned char)socksreq[7],
              (unsigned int)ntohs(*(unsigned short*)(&socksreq[8])),
              socksreq[1]);
        return 1;
    }
  }

  Curl_nonblock(sock, TRUE);
  return 0; /* Proxy was successful! */
}