void Curl_tcpnodelay(struct connectdata *conn, curl_socket_t sockfd)
{
#if defined(TCP_NODELAY)
#if !defined(CURL_DISABLE_VERBOSE_STRINGS)
  struct Curl_easy *data = conn->data;
#endif
  curl_socklen_t onoff = (curl_socklen_t) 1;
  int level = IPPROTO_TCP;

#if defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) conn;
#endif

  if(setsockopt(sockfd, level, TCP_NODELAY, (void *)&onoff,
                sizeof(onoff)) < 0)
    infof(data, "Could not set TCP_NODELAY: %s\n",
          Curl_strerror(conn, SOCKERRNO));
  else
    infof(data, "TCP_NODELAY set\n");
#else
  (void)conn;
  (void)sockfd;
#endif
}