static
int socketerror(int sockfd)
{
  int err = 0;
  socklen_t errSize = sizeof(err);

  if( -1 == getsockopt(sockfd, SOL_SOCKET, SO_ERROR,
                       (void *)&err, &errSize))
    err = ourerrno();
  
  return err;
}