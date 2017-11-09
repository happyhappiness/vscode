CURLcode Curl_read_plain(curl_socket_t sockfd,
                         char *buf,
                         size_t bytesfromsocket,
                         ssize_t *n)
{
  ssize_t nread = sread(sockfd, buf, bytesfromsocket);

  if(-1 == nread) {
    int err = SOCKERRNO;
    int return_error;
#ifdef USE_WINSOCK
    return_error = WSAEWOULDBLOCK == err;
#else
    return_error = EWOULDBLOCK == err || EAGAIN == err || EINTR == err;
#endif
    if(return_error)
      return CURLE_AGAIN;
    return CURLE_RECV_ERROR;
  }

  /* we only return number of bytes read when we return OK */
  *n = nread;
  return CURLE_OK;
}