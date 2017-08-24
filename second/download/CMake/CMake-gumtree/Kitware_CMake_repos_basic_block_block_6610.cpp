{
    /* file descriptor for the socket */
    transport_ptr = GNUTLS_INT_TO_POINTER_CAST(conn->sock[sockindex]);
    gnutls_transport_push = Curl_gtls_push;
    gnutls_transport_pull = Curl_gtls_pull;
  }