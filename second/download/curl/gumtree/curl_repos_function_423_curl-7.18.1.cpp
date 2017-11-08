int Curl_resolv_getsock(struct connectdata *conn,
                        curl_socket_t *socks,
                        int numsocks)
{
  const struct thread_data *td =
    (const struct thread_data *) conn->async.os_specific;

  if(td && td->dummy_sock != CURL_SOCKET_BAD) {
    if(numsocks) {
      /* return one socket waiting for writable, even though this is just
         a dummy */
      socks[0] = td->dummy_sock;
      return GETSOCK_WRITESOCK(0);
    }
  }
  return 0;
}