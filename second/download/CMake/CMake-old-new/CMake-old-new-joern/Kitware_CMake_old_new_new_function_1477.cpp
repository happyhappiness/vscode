static void verboseconnect(struct connectdata *conn,
                           struct Curl_dns_entry *dns)
{
#ifdef HAVE_INET_NTOA_R
  char ntoa_buf[64];
#endif
  struct SessionHandle *data = conn->data;

  /* Figure out the ip-number and display the first host name it shows: */
#ifdef ENABLE_IPV6
  (void)dns; /* not used in the IPv6 enabled version */
  {
    char hbuf[NI_MAXHOST];
#ifdef NI_WITHSCOPEID
    const int niflags = NI_NUMERICHOST | NI_WITHSCOPEID;
#else
    const int niflags = NI_NUMERICHOST;
#endif
    struct addrinfo *ai = conn->serv_addr;

    if (getnameinfo(ai->ai_addr, ai->ai_addrlen, hbuf, sizeof(hbuf), NULL, 0,
        niflags)) {
      snprintf(hbuf, sizeof(hbuf), "?");
    }
    if (ai->ai_canonname) {
      infof(data, "Connected to %s (%s) port %d\n", ai->ai_canonname, hbuf,
            conn->port);
    } else {
      infof(data, "Connected to %s port %d\n", hbuf, conn->port);
    }
  }
#else
  {
    Curl_addrinfo *hostaddr=dns->addr;
    struct in_addr in;
    (void) memcpy(&in.s_addr, &conn->serv_addr.sin_addr, sizeof (in.s_addr));
    infof(data, "Connected to %s (%s) port %d\n",
          hostaddr?hostaddr->h_name:"",
#if defined(HAVE_INET_NTOA_R)
          inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf)),
#else
          inet_ntoa(in),
#endif
          conn->port);
  }
#endif
}