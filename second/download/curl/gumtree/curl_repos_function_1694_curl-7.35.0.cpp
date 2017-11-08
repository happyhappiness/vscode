static CURLcode
socket_write(struct connectdata *conn, curl_socket_t fd, const void *to,
             size_t len)
{
  const char *to_p = to;
  CURLcode code;
  ssize_t written;

  while(len > 0) {
    code = Curl_write_plain(conn, fd, to_p, len, &written);
    if(code == CURLE_OK) {
      len -= written;
      to_p += written;
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