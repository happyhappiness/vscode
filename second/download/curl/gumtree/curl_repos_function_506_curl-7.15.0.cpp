CURLcode Curl_write(struct connectdata *conn,
                    curl_socket_t sockfd,
                    void *mem,
                    size_t len,
                    ssize_t *written)
{
  ssize_t bytes_written;
  CURLcode retcode;
  int num = (sockfd == conn->sock[SECONDARYSOCKET]);

  if (conn->ssl[num].use)
    /* only TRUE if SSL enabled */
    bytes_written = Curl_ssl_send(conn, num, mem, len);
  else {
    if(conn->sec_complete)
      /* only TRUE if krb4 enabled */
      bytes_written = Curl_sec_write(conn, sockfd, mem, len);
    else
      bytes_written = (ssize_t)swrite(sockfd, mem, len);

    if(-1 == bytes_written) {
      int err = Curl_ourerrno();

      if(
#ifdef WSAEWOULDBLOCK
        /* This is how Windows does it */
        (WSAEWOULDBLOCK == err)
#else
        /* As pointed out by Christophe Demory on March 11 2003, errno
           may be EWOULDBLOCK or on some systems EAGAIN when it returned
           due to its inability to send off data without blocking. We
           therefor treat both error codes the same here */
        (EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err)
#endif
        )
        /* this is just a case of EWOULDBLOCK */
        bytes_written=0;
      else
        failf(conn->data, "Send failure: %s",
              Curl_strerror(conn, err));
    }
  }
  *written = bytes_written;
  retcode = (-1 != bytes_written)?CURLE_OK:CURLE_SEND_ERROR;

  return retcode;
}