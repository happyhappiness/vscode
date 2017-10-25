static void tcpnodelay(struct connectdata *conn,
                       curl_socket_t sockfd)
{
#ifdef TCP_NODELAY
  struct SessionHandle *data= conn->data;
  socklen_t onoff = (socklen_t) data->set.tcp_nodelay;
  if(setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (void *)&onoff,
                sizeof(onoff)) < 0)
    infof(data, "Could not set TCP_NODELAY: %s\n",
          Curl_strerror(conn, Curl_ourerrno()));
  else
    infof(data,"TCP_NODELAY set\n");
#else
  (void)conn;
  (void)sockfd;
#endif
}