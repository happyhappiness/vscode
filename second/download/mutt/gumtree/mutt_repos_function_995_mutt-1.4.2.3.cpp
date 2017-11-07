static int
mutt_nss_socket_read (CONNECTION* conn, char* buf, size_t len)
{
  return PR_Read (((mutt_nss_t*) conn->sockdata)->fd, buf, len);
}