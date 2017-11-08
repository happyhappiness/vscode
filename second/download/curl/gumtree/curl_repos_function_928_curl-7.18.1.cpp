ssize_t
Curl_sec_send(struct connectdata *conn, int num, char *buffer, int length)
{
  curl_socket_t fd = conn->sock[num];
  return (ssize_t)Curl_sec_write(conn, fd, buffer, length);
}