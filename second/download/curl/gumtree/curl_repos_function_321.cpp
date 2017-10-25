int curl_socket(int domain, int type, int protocol, int line,
                const char *source)
{
  int sockfd=(socket)(domain, type, protocol);
  if(logfile && (sockfd!=-1))
    fprintf(logfile, "FD %s:%d socket() = %d\n",
            source, line, sockfd);
  return sockfd;
}