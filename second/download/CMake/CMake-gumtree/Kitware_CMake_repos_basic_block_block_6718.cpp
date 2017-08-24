{
    failf(conn->data, "GnuTLS recv error (%d): %s",
          (int)ret, gnutls_strerror((int)ret));
    *curlcode = CURLE_RECV_ERROR;
    return -1;
  }