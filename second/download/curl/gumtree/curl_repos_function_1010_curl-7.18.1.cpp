int Curl_resolv_getsock(struct connectdata *conn,
                        curl_socket_t *sock,
                        int numsocks)
{
  (void)conn;
  (void)sock;
  (void)numsocks;

  return 0; /* no bits since we don't use any socks */
}