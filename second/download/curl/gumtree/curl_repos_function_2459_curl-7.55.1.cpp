int Curl_ssl_getsock(struct connectdata *conn,
                     curl_socket_t *socks,
                     int numsocks)
{
  (void)conn;
  (void)socks;
  (void)numsocks;
  return GETSOCK_BLANK;
}