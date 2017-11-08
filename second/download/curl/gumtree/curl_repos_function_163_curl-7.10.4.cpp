int curl_socket(int domain, int type, int protocol, int line, char *source)
{
  int sockfd=(socket)(domain, type, protocol);
  if(logfile)
    fprintf(logfile, "FD %s:%d socket() = %d\n",
            source, line, sockfd);
  return sockfd;
}