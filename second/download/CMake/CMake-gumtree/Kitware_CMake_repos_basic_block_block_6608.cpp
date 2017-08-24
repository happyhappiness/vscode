{
      failf(data, "gnutls_ocsp_status_request_enable_client() failed: %d", rc);
      return CURLE_SSL_CONNECT_ERROR;
    }