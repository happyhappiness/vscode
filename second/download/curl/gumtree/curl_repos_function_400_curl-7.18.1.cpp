inline static int Curl_hp_accept(int sockfd, struct sockaddr *addr,
                                 socklen_t *addrlen)
{
  int rc;
  if(addrlen) {
     int len = *addrlen;
     rc = accept(sockfd, addr, &len);
     *addrlen = len;
  }
  else
     rc = accept(sockfd, addr, 0);
  return rc;
}