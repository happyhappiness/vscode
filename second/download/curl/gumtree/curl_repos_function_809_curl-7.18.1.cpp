CURLcode Curl_write(struct connectdata *conn,
                    curl_socket_t sockfd,
                    void *mem,
                    size_t len,
                    ssize_t *written)
{
  ssize_t bytes_written;
  CURLcode retcode;
  int num = (sockfd == conn->sock[SECONDARYSOCKET]);

  if(conn->ssl[num].state == ssl_connection_complete)
    /* only TRUE if SSL enabled */
    bytes_written = Curl_ssl_send(conn, num, mem, len);
#ifdef USE_LIBSSH2
  else if(conn->protocol & PROT_SCP)
    bytes_written = Curl_scp_send(conn, num, mem, len);
  else if(conn->protocol & PROT_SFTP)
    bytes_written = Curl_sftp_send(conn, num, mem, len);
#endif /* !USE_LIBSSH2 */
  else if(conn->sec_complete)
    /* only TRUE if krb enabled */
    bytes_written = Curl_sec_send(conn, num, mem, len);
  else
    bytes_written = send_plain(conn, num, mem, len);

  *written = bytes_written;
  retcode = (-1 != bytes_written)?CURLE_OK:CURLE_SEND_ERROR;

  return retcode;
}