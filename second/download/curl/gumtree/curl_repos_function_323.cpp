int curl_sclose(int sockfd, int line, const char *source)
{
  int res=sclose(sockfd);
  if(logfile)
    fprintf(logfile, "FD %s:%d sclose(%d)\n",
            source, line, sockfd);
  return res;
}