{
    const char * const dispname = SSL_IS_PROXY() ?
      conn->http_proxy.host.dispname : conn->host.dispname;

    if(SSL_CONN_CONFIG(verifyhost)) {
      failf(data, "SSL: certificate subject name (%s) does not match "
            "target host name '%s'", certbuf, dispname);
      gnutls_x509_crt_deinit(x509_cert);
      return CURLE_PEER_FAILED_VERIFICATION;
    }
    else
      infof(data, "\t common name: %s (does not match '%s')\n",
            certbuf, dispname);
  }