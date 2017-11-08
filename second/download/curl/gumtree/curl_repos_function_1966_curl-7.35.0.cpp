CURLcode Curl_qsossl_connect(struct connectdata * conn, int sockindex)

{
  struct SessionHandle * data = conn->data;
  struct ssl_connect_data * connssl = &conn->ssl[sockindex];
  int rc;

  rc = Curl_qsossl_init_session(data);

  if(rc == CURLE_OK) {
    rc = Curl_qsossl_create(conn, sockindex);

    if(rc == CURLE_OK) {
      rc = Curl_qsossl_handshake(conn, sockindex);
      if(rc != CURLE_OK)
        SSL_Destroy(connssl->handle);
    }
  }

  if(rc == CURLE_OK) {
    conn->recv[sockindex] = qsossl_recv;
    conn->send[sockindex] = qsossl_send;
    connssl->state = ssl_connection_complete;
  }
  else {
    connssl->handle = NULL;
    connssl->use = FALSE;
    connssl->state = ssl_connection_none;
  }

  return rc;
}