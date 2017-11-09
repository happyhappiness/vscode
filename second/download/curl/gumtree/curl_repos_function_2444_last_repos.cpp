static void close_one(struct ssl_connect_data *connssl,
                      struct connectdata *conn, int sockindex)
{
  if(BACKEND->handle) {
    gskit_status(conn->data, gsk_secure_soc_close(&BACKEND->handle),
              "gsk_secure_soc_close()", 0);
    /* Last chance to drain output. */
    while(pipe_ssloverssl(conn, sockindex, SOS_WRITE) > 0)
      ;
    BACKEND->handle = (gsk_handle) NULL;
    if(BACKEND->localfd >= 0) {
      close(BACKEND->localfd);
      BACKEND->localfd = -1;
    }
    if(BACKEND->remotefd >= 0) {
      close(BACKEND->remotefd);
      BACKEND->remotefd = -1;
    }
  }
  if(BACKEND->iocport >= 0)
    close_async_handshake(connssl);
}