static ssize_t send_plain(struct connectdata *conn,
                          int num,
                          void *mem,
                          size_t len)
{
  curl_socket_t sockfd = conn->sock[num];
  ssize_t bytes_written = swrite(sockfd, mem, len);

  if(-1 == bytes_written) {
    int err = SOCKERRNO;

    if(
#ifdef WSAEWOULDBLOCK
      /* This is how Windows does it */
      (WSAEWOULDBLOCK == err)
#else
      /* errno may be EWOULDBLOCK or on some systems EAGAIN when it returned
         due to its inability to send off data without blocking. We therefor
         treat both error codes the same here */
      (EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err)
#endif
      )
      /* this is just a case of EWOULDBLOCK */
      bytes_written=0;
    else
      failf(conn->data, "Send failure: %s",
            Curl_strerror(conn, err));
  }
  return bytes_written;
}