int curl_sclose(int sockfd, int line, char *source)
{
  int res=sclose(sockfd);
  fprintf(logfile?logfile:stderr, "FD %s:%d sclose(%d)\n",
          source, line, sockfd);
  return res;
}