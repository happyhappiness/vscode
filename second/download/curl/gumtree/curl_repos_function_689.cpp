CURLcode Curl_resolv_fdset(struct connectdata *conn,
                           fd_set *read_fd_set,
                           fd_set *write_fd_set,
                           int *max_fdp)

{
  int max = ares_fds(conn->data->state.areschannel,
                     read_fd_set, write_fd_set);
  *max_fdp = max;

  return CURLE_OK;
}