static void tcpnodelay(struct connectdata *conn,
                       curl_socket_t sockfd)
{
#ifdef TCP_NODELAY
  struct SessionHandle *data= conn->data;
  socklen_t onoff = (socklen_t) data->set.tcp_nodelay;
  int proto = IPPROTO_TCP;

#ifdef HAVE_GETPROTOBYNAME
  struct protoent *pe = getprotobyname("tcp");
  if(pe)
    proto = pe->p_proto;
#endif

  if(setsockopt(sockfd, proto, TCP_NODELAY, (void *)&onoff,
                sizeof(onoff)) < 0)
    infof(data, "Could not set TCP_NODELAY: %s\n",
          Curl_strerror(conn, SOCKERRNO));
  else
    infof(data,"TCP_NODELAY set\n");
#else
  (void)conn;
  (void)sockfd;
#endif
}