void Curl_updateconninfo(struct connectdata *conn, curl_socket_t sockfd)
{
  curl_socklen_t len;
  struct Curl_sockaddr_storage ssrem;
  struct Curl_sockaddr_storage ssloc;
  struct Curl_easy *data = conn->data;

  if(conn->socktype == SOCK_DGRAM)
    /* there's no connection! */
    return;

  if(!conn->bits.reuse && !conn->bits.tcp_fastopen) {
    len = sizeof(struct Curl_sockaddr_storage);
    if(getpeername(sockfd, (struct sockaddr*) &ssrem, &len)) {
      int error = SOCKERRNO;
      failf(data, "getpeername() failed with errno %d: %s",
            error, Curl_strerror(conn, error));
      return;
    }

    len = sizeof(struct Curl_sockaddr_storage);
    memset(&ssloc, 0, sizeof(ssloc));
    if(getsockname(sockfd, (struct sockaddr*) &ssloc, &len)) {
      int error = SOCKERRNO;
      failf(data, "getsockname() failed with errno %d: %s",
            error, Curl_strerror(conn, error));
      return;
    }

    if(!getaddressinfo((struct sockaddr*)&ssrem,
                        conn->primary_ip, &conn->primary_port)) {
      failf(data, "ssrem inet_ntop() failed with errno %d: %s",
            errno, Curl_strerror(conn, errno));
      return;
    }
    memcpy(conn->ip_addr_str, conn->primary_ip, MAX_IPADR_LEN);

    if(!getaddressinfo((struct sockaddr*)&ssloc,
                       conn->local_ip, &conn->local_port)) {
      failf(data, "ssloc inet_ntop() failed with errno %d: %s",
            errno, Curl_strerror(conn, errno));
      return;
    }

  }

  /* persist connection info in session handle */
  Curl_persistconninfo(conn);
}