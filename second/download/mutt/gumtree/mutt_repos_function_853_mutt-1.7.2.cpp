static int ssl_socket_open_err (CONNECTION *conn)
{
  mutt_error (_("SSL disabled due to the lack of entropy"));
  mutt_sleep (2);
  return -1;
}