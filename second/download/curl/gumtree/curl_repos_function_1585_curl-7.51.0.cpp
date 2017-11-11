static void pre_receive_plain(struct connectdata *conn, int num)
{
  const curl_socket_t sockfd = conn->sock[num];
  struct postponed_data * const psnd = &(conn->postponed[num]);
  size_t bytestorecv = psnd->allocated_size - psnd->recv_size;
  /* WinSock will destroy unread received data if send() is
     failed.
     To avoid lossage of received data, recv() must be
     performed before every send() if any incoming data is
     available. However, skip this, if buffer is already full. */
  if((conn->handler->protocol&PROTO_FAMILY_HTTP) != 0 &&
     conn->recv[num] == Curl_recv_plain &&
     (!psnd->buffer || bytestorecv)) {
    const int readymask = Curl_socket_check(sockfd, CURL_SOCKET_BAD,
                                            CURL_SOCKET_BAD, 0);
    if(readymask != -1 && (readymask & CURL_CSELECT_IN) != 0) {
      /* Have some incoming data */
      if(!psnd->buffer) {
        /* Use buffer double default size for intermediate buffer */
        psnd->allocated_size = 2 * BUFSIZE;
        psnd->buffer = malloc(psnd->allocated_size);
        psnd->recv_size = 0;
        psnd->recv_processed = 0;
#ifdef DEBUGBUILD
        psnd->bindsock = sockfd; /* Used only for DEBUGASSERT */
#endif /* DEBUGBUILD */
        bytestorecv = psnd->allocated_size;
      }
      if(psnd->buffer) {
        ssize_t recvedbytes;
        DEBUGASSERT(psnd->bindsock == sockfd);
        recvedbytes = sread(sockfd, psnd->buffer + psnd->recv_size,
                            bytestorecv);
        if(recvedbytes > 0)
          psnd->recv_size += recvedbytes;
      }
      else
        psnd->allocated_size = 0;
    }
  }
}