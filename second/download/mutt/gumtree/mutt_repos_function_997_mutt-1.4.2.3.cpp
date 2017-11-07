int
mutt_nss_socket_setup (CONNECTION * con)
{
  if (mutt_nss_init ())
    return -1;
  con->open = mutt_nss_socket_open;
  con->read = mutt_nss_socket_read;
  con->write = mutt_nss_socket_write;
  con->close = mutt_nss_socket_close;
  return 0;
}