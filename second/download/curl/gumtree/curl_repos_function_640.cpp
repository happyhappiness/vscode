CURLcode Curl_resolv_fdset(struct connectdata *conn,
                           fd_set *read_fd_set,
                           fd_set *write_fd_set,
                           int *max_fdp)
{
  (void)conn;
  (void)read_fd_set;
  (void)write_fd_set;
  (void)max_fdp;

  return CURLE_OK;
}