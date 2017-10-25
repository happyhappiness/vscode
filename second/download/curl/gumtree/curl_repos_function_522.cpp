CURLcode Curl_ftp_fdset(struct connectdata *conn,
                        fd_set *read_fd_set,
                        fd_set *write_fd_set,
                        int *max_fdp)
{
  struct FTP *ftp = conn->proto.ftp;
  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];

  if(ftp->sendleft) {
    /* write mode */
    FD_SET(sockfd, write_fd_set);
  }
  else {
    /* read mode */
    FD_SET(sockfd, read_fd_set);
  }

  if((int)sockfd > *max_fdp)
    *max_fdp = (int)sockfd;

  return CURLE_OK;
}