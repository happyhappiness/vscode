CURLcode Curl_resolv_fdset(struct connectdata *conn,
                           fd_set *read_fd_set,
                           fd_set *write_fd_set,
                           int *max_fdp)
{
  const struct thread_data *td =
    (const struct thread_data *) conn->async.os_specific;

  if (td && td->dummy_sock != CURL_SOCKET_BAD) {
    FD_SET(td->dummy_sock,write_fd_set);
    *max_fdp = (int)td->dummy_sock;
  }
  (void) read_fd_set;
  return CURLE_OK;
}