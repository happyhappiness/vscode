void Curl_single_fdset(struct connectdata *conn,
                       fd_set *read_fd_set,
                       fd_set *write_fd_set,
                       fd_set *exc_fd_set,
                       int *max_fd)
{
  *max_fd = -1; /* init */
  if(conn->keep.keepon & KEEP_READ) {
    FD_SET(conn->sockfd, read_fd_set);
    *max_fd = (int)conn->sockfd;
  }
  if(conn->keep.keepon & KEEP_WRITE) {
    FD_SET(conn->writesockfd, write_fd_set);

    /* since sockets are curl_socket_t nowadays, we typecast it to int here
       to compare it nicely */
    if((int)conn->writesockfd > *max_fd)
      *max_fd = (int)conn->writesockfd;
  }
  /* we don't use exceptions, only touch that one to prevent compiler
     warnings! */
  *exc_fd_set = *exc_fd_set;
}