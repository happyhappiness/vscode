int Curl_resolver_getsock(struct connectdata *conn,
                          curl_socket_t *socks,
                          int numsocks)
{
  (void)conn;
  (void)socks;
  (void)numsocks;
  return 0;
}