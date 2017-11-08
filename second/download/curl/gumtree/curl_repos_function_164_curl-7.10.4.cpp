int curl_accept(int s, struct sockaddr *addr, socklen_t *addrlen,
                int line, const char *source)
{
  int sockfd=(accept)(s, addr, addrlen);
  if(logfile)
    fprintf(logfile, "FD %s:%d accept() = %d\n",
            source, line, sockfd);
  return sockfd;
}