CURLcode Curl_doing_fdset(struct connectdata *conn,
                          fd_set *read_fd_set,
                          fd_set *write_fd_set,
                          int *max_fdp)
{
  CURLcode res = CURLE_OK;
  if(conn && conn->curl_doing_fdset)
    res = conn->curl_doing_fdset(conn, read_fd_set, write_fd_set, max_fdp);
  return res;
}