int curl_sclose(curl_socket_t sockfd, int line, const char *source)
{
  int res=sclose(sockfd);
  curl_mark_sclose(sockfd, line, source);
  return res;
}