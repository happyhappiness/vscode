CURLcode Curl_read_plain(curl_socket_t sockfd,
                         char *buf,
                         size_t bytesfromsocket,
                         ssize_t *n)
{
  ssize_t nread = sread(sockfd, buf, bytesfromsocket);

  if(-1 == nread) {
    int err = SOCKERRNO;
#ifdef USE_WINSOCK
    if(WSAEWOULDBLOCK == err)
#else
    if((EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err))
#endif
      return CURLE_AGAIN;
    else
      return CURLE_RECV_ERROR;
  }

  /* we only return number of bytes read when we return OK */
  *n = nread;
  return CURLE_OK;
}