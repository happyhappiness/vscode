static int Curl_gtls_shutdown(struct connectdata *conn, int sockindex)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  ssize_t result;
  int retval = 0;
  struct Curl_easy *data = conn->data;
  int done = 0;
  char buf[120];

  /* This has only been tested on the proftpd server, and the mod_tls code
     sends a close notify alert without waiting for a close notify alert in
     response. Thus we wait for a close notify alert from the server, but
     we do not send one. Let's hope other servers do the same... */

  if(data->set.ftp_ccc == CURLFTPSSL_CCC_ACTIVE)
      gnutls_bye(BACKEND->session, GNUTLS_SHUT_WR);

  if(BACKEND->session) {
    while(!done) {
      int what = SOCKET_READABLE(conn->sock[sockindex],
                                 SSL_SHUTDOWN_TIMEOUT);
      if(what > 0) {
        /* Something to read, let's do it and hope that it is the close
           notify alert from the server */
        result = gnutls_record_recv(BACKEND->session,
                                    buf, sizeof(buf));
        switch(result) {
        case 0:
          /* This is the expected response. There was no data but only
             the close notify alert */
          done = 1;
          break;
        case GNUTLS_E_AGAIN:
        case GNUTLS_E_INTERRUPTED:
          infof(data, "GNUTLS_E_AGAIN || GNUTLS_E_INTERRUPTED\n");
          break;
        default:
          retval = -1;
          done = 1;
          break;
        }
      }
      else if(0 == what) {
        /* timeout */
        failf(data, "SSL shutdown timeout");
        done = 1;
        break;
      }
      else {
        /* anything that gets here is fatally bad */
        failf(data, "select/poll on SSL socket, errno: %d", SOCKERRNO);
        retval = -1;
        done = 1;
      }
    }
    gnutls_deinit(BACKEND->session);
  }
  gnutls_certificate_free_credentials(BACKEND->cred);

#ifdef USE_TLS_SRP
  if(SSL_SET_OPTION(authtype) == CURL_TLSAUTH_SRP
     && SSL_SET_OPTION(username) != NULL)
    gnutls_srp_free_client_credentials(BACKEND->srp_client_cred);
#endif

  BACKEND->cred = NULL;
  BACKEND->session = NULL;

  return retval;
}