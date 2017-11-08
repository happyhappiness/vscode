int curl_accept(int s, void *saddr, void *saddrlen,
                int line, const char *source)
{
  struct sockaddr *addr = (struct sockaddr *)saddr;
  socklen_t *addrlen = (socklen_t *)saddrlen;
  int sockfd=(accept)(s, addr, addrlen);
  if(logfile)
    fprintf(logfile, "FD %s:%d accept() = %d\n",
            source, line, sockfd);
  return sockfd;
}