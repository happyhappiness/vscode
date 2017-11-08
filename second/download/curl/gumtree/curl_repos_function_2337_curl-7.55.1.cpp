static void close_one(struct ssl_connect_data *connssl,
                      struct connectdata *conn, int sockindex)
{
  if(connssl->handle) {
    gskit_status(conn->data, gsk_secure_soc_close(&connssl->handle),
              "gsk_secure_soc_close()", 0);
    /* Last chance to drain output. */
    while(pipe_ssloverssl(conn, sockindex, SOS_WRITE) > 0)
      ;
    connssl->handle = (gsk_handle) NULL;
    if(connssl->localfd >= 0) {
      close(connssl->localfd);
      connssl->localfd = -1;
    }
    if(connssl->remotefd >= 0) {
      close(connssl->remotefd);
      connssl->remotefd = -1;
    }
  }
  if(connssl->iocport >= 0)
    close_async_handshake(connssl);
}