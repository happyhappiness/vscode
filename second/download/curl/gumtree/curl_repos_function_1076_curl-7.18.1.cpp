static CURLcode handshake(struct connectdata *conn,
                          gnutls_session session,
                          int sockindex,
                          bool duringconnect)
{
  struct SessionHandle *data = conn->data;
  int rc;
  if(!gtls_inited)
    _Curl_gtls_init();
  do {
    rc = gnutls_handshake(session);

    if((rc == GNUTLS_E_AGAIN) || (rc == GNUTLS_E_INTERRUPTED)) {
      long timeout_ms = Curl_timeleft(conn, NULL, duringconnect);

      if(timeout_ms < 0) {
        /* a precaution, no need to continue if time already is up */
        failf(data, "SSL connection timeout");
        return CURLE_OPERATION_TIMEDOUT;
      }

      rc = Curl_socket_ready(conn->sock[sockindex],
                       conn->sock[sockindex], (int)timeout_ms);
      if(rc > 0)
        /* reabable or writable, go loop*/
        continue;
      else if(0 == rc) {
        /* timeout */
        failf(data, "SSL connection timeout");
        return CURLE_OPERATION_TIMEDOUT;
      }
      else {
        /* anything that gets here is fatally bad */
        failf(data, "select/poll on SSL socket, errno: %d", SOCKERRNO);
        return CURLE_SSL_CONNECT_ERROR;
      }
    }
    else
      break;
  } while(1);

  if(rc < 0) {
    failf(data, "gnutls_handshake() failed: %s", gnutls_strerror(rc));
    return CURLE_SSL_CONNECT_ERROR;
  }

  return CURLE_OK;
}