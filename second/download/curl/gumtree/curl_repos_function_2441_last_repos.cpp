static void close_async_handshake(struct ssl_connect_data *connssl)
{
  QsoDestroyIOCompletionPort(BACKEND->iocport);
  BACKEND->iocport = -1;
}