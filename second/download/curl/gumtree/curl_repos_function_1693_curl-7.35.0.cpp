static CURLcode
socket_read(curl_socket_t fd, void *to, size_t len)
{
  char *to_p = to;
  CURLcode code;
  ssize_t nread;

  while(len > 0) {
    code = Curl_read_plain(fd, to_p, len, &nread);
    if(code == CURLE_OK) {
      len -= nread;
      to_p += nread;
    }
    else {
      /* FIXME: We are doing a busy wait */
      if(code == CURLE_AGAIN)
        continue;
      return code;
    }
  }
  return CURLE_OK;
}