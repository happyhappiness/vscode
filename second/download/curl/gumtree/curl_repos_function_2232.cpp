int Curl_axtls_shutdown(struct connectdata *conn, int sockindex)
{
  /* Outline taken from openssl.c since functions are in axTLS compat layer.
     axTLS's error set is much smaller, so a lot of error-handling was removed.
   */
  int retval = 0;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct SessionHandle *data = conn->data;
  uint8_t *buf;
  ssize_t nread;

  infof(conn->data, "  Curl_axtls_shutdown\n");

  /* This has only been tested on the proftpd server, and the mod_tls code
     sends a close notify alert without waiting for a close notify alert in
     response. Thus we wait for a close notify alert from the server, but
     we do not send one. Let's hope other servers do the same... */

  /* axTLS compat layer does nothing for SSL_shutdown, so we do nothing too
  if(data->set.ftp_ccc == CURLFTPSSL_CCC_ACTIVE)
      (void)SSL_shutdown(connssl->ssl);
  */

  if(connssl->ssl) {
    int what = Curl_socket_ready(conn->sock[sockindex],
                                 CURL_SOCKET_BAD, SSL_SHUTDOWN_TIMEOUT);
    if(what > 0) {
      /* Something to read, let's do it and hope that it is the close
         notify alert from the server.  buf is managed internally by
         axTLS and will be released upon calling ssl_free via
         free_ssl_structs. */
      nread = (ssize_t)ssl_read(connssl->ssl, &buf);

      if(nread < SSL_OK) {
        failf(data, "close notify alert not received during shutdown");
        retval = -1;
      }
    }
    else if(0 == what) {
      /* timeout */
      failf(data, "SSL shutdown timeout");
    }
    else {
      /* anything that gets here is fatally bad */
      failf(data, "select/poll on SSL socket, errno: %d", SOCKERRNO);
      retval = -1;
    }

    free_ssl_structs(connssl);
  }
  return retval;
}