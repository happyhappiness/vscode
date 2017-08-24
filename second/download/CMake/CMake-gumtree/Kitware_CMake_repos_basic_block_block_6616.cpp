{
#if HAVE_GNUTLS_CERTIFICATE_SET_X509_KEY_FILE2
      const unsigned int supported_key_encryption_algorithms =
        GNUTLS_PKCS_USE_PKCS12_3DES | GNUTLS_PKCS_USE_PKCS12_ARCFOUR |
        GNUTLS_PKCS_USE_PKCS12_RC2_40 | GNUTLS_PKCS_USE_PBES2_3DES |
        GNUTLS_PKCS_USE_PBES2_AES_128 | GNUTLS_PKCS_USE_PBES2_AES_192 |
        GNUTLS_PKCS_USE_PBES2_AES_256;
      rc = gnutls_certificate_set_x509_key_file2(
           conn->ssl[sockindex].cred,
           SSL_SET_OPTION(cert),
           SSL_SET_OPTION(key) ?
           SSL_SET_OPTION(key) : SSL_SET_OPTION(cert),
           do_file_type(SSL_SET_OPTION(cert_type)),
           SSL_SET_OPTION(key_passwd),
           supported_key_encryption_algorithms);
      if(rc != GNUTLS_E_SUCCESS) {
        failf(data,
              "error reading X.509 potentially-encrypted key file: %s",
              gnutls_strerror(rc));
        return CURLE_SSL_CONNECT_ERROR;
      }
#else
      failf(data, "gnutls lacks support for encrypted key files");
      return CURLE_SSL_CONNECT_ERROR;
#endif
    }