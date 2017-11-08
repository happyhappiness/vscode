static CURLcode
socket_read(curl_socket_t fd, void *to, size_t len)
{
  char *to_p = to;
  CURLcode result;
  ssize_t nread;

  while(len > 0) {
    result = Curl_read_plain(fd, to_p, len, &nread);
    if(!result) {
      len -= nread;
      to_p += nread;
    }
    else {
      /* FIXME: We are doing a busy wait */
      if(result == CURLE_AGAIN)
        continue;
      return result;
    }
  }
  return CURLE_OK;
}