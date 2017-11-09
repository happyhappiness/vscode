ssize_t Curl_recv_plain(struct connectdata *conn, int num, char *buf,
                        size_t len, CURLcode *code)
{
  curl_socket_t sockfd = conn->sock[num];
  ssize_t nread;
  /* Check and return data that already received and storied in internal
     intermediate buffer */
  nread = get_pre_recved(conn, num, buf, len);
  if(nread > 0) {
    *code = CURLE_OK;
    return nread;
  }

  nread = sread(sockfd, buf, len);

  *code = CURLE_OK;
  if(-1 == nread) {
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
      ) {
      /* this is just a case of EWOULDBLOCK */
      *code = CURLE_AGAIN;
    }
    else {
      failf(conn->data, "Recv failure: %s",
            Curl_strerror(conn, err));
      conn->data->state.os_errno = err;
      *code = CURLE_RECV_ERROR;
    }
  }
  return nread;
}