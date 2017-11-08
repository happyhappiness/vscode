void Curl_tcpnodelay(struct connectdata *conn, curl_socket_t sockfd)
{
#if defined(TCP_NODELAY)
#if !defined(CURL_DISABLE_VERBOSE_STRINGS)
  struct Curl_easy *data = conn->data;
#endif
  curl_socklen_t onoff = (curl_socklen_t) 1;
  int level = IPPROTO_TCP;

#if 0
  /* The use of getprotobyname() is disabled since it isn't thread-safe on
     numerous systems. On these getprotobyname_r() should be used instead, but
     that exists in at least one 4 arg version and one 5 arg version, and
     since the proto number rarely changes anyway we now just use the hard
     coded number. The "proper" fix would need a configure check for the
     correct function much in the same style the gethostbyname_r versions are
     detected. */
  struct protoent *pe = getprotobyname("tcp");
  if(pe)
    level = pe->p_proto;
#endif

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