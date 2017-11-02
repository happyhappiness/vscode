static void close_async_handshake(struct ssl_connect_data *connssl)
{
  QsoDestroyIOCompletionPort(connssl->iocport);
  connssl->iocport = -1;
}