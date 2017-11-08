void Curl_single_fdset(struct connectdata *conn,
                       fd_set *read_fd_set,
                       fd_set *write_fd_set,
                       fd_set *exc_fd_set,
                       int *max_fd)
{
  *max_fd = -1; /* init */
  if(conn->keep.keepon & KEEP_READ) {
    FD_SET(conn->sockfd, read_fd_set);
    *max_fd = conn->sockfd;
    conn->keep.readfdp = read_fd_set; /* store the address of the set */
  }
  if(conn->keep.keepon & KEEP_WRITE) {
    FD_SET(conn->writesockfd, write_fd_set);
    if(conn->writesockfd > *max_fd)
      *max_fd = conn->writesockfd;
    conn->keep.writefdp = write_fd_set; /* store the address of the set */
  }
  /* we don't use exceptions, only touch that one to prevent compiler
     warnings! */
  *exc_fd_set = *exc_fd_set;
}