static int
mutt_nss_socket_write (CONNECTION * con, const char *buf, size_t count)
{
  return PR_Write (((mutt_nss_t *) con->sockdata)->fd, buf, count);
}