static int handleSock5Proxy(
    const char *proxy_name,
    const char *proxy_password,
    struct connectdata *conn,
    int sock)
{
  unsigned char socksreq[600]; /* room for large user/pw (255 max each) */
  ssize_t actualread;
  ssize_t written;
  CURLcode result;

  Curl_nonblock(sock, FALSE);

  socksreq[0] = 5; /* version */
  socksreq[1] = (char)(proxy_name[0] ? 2 : 1); /* number of methods (below) */
  socksreq[2] = 0; /* no authentication */
  socksreq[3] = 2; /* username/password */

  result = Curl_write(conn, sock, (char *)socksreq, (2 + (int)socksreq[1]),
                      &written);
  if ((result != CURLE_OK) || (written != (2 + (int)socksreq[1]))) {
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

    userlen = strlen(proxy_name);
    pwlen = strlen(proxy_password);

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

    result = Curl_write(conn, sock, (char *)socksreq, len, &written);
    if ((result != CURLE_OK) || (len != written)) {
      failf(conn->data, "Failed to send SOCKS5 sub-negotiation request.");
      return 1;
    }

    result=Curl_read(conn, sock, (char *)socksreq, 2, &actualread);
    if ((result != CURLE_OK) || (actualread != 2)) {
      failf(conn->data, "Unable to receive SOCKS5 sub-negotiation response.");
      return 1;
    }

    if ((socksreq[0] != 5) || /* version */
        (socksreq[1] != 0)) { /* status */
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
      if (proxy_name[0] == 0) {
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
#ifndef ENABLE_IPV6
    struct Curl_dns_entry *dns;
    Curl_addrinfo *hp=NULL;
    dns = Curl_resolv(conn->data, conn->hostname, conn->remote_port);
    /*
     * We cannot use 'hostent' as a struct that Curl_resolv() returns.  It
     * returns a Curl_addrinfo pointer that may not always look the same.
     */
    if(dns)
      hp=dns->addr;
    if (hp && hp->h_addr_list[0]) {
      socksreq[4] = ((char*)hp->h_addr_list[0])[0];