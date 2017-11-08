static void nosigpipe(struct connectdata *conn,
                      curl_socket_t sockfd)
{
  struct SessionHandle *data= conn->data;
  int onoff = 1;
  if(setsockopt(sockfd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&onoff,
                sizeof(onoff)) < 0)
    infof(data, "Could not set SO_NOSIGPIPE: %s\n",
          Curl_strerror(conn, Curl_ourerrno()));
}