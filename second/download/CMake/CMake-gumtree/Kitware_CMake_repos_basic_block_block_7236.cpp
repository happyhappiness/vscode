{
  if(curlssl_shutdown(conn, sockindex))
    return CURLE_SSL_SHUTDOWN_FAILED;

  conn->ssl[sockindex].use = FALSE; /* get back to ordinary socket usage */
  conn->ssl[sockindex].state = ssl_connection_none;

  conn->recv[sockindex] = Curl_recv_plain;
  conn->send[sockindex] = Curl_send_plain;

  return CURLE_OK;
}