int is_a_socket(int fd)
{
  int v,l;
  l = sizeof(int);
  return(getsockopt(fd, SOL_SOCKET, SO_TYPE, (char *)&v, &l) == 0);
}