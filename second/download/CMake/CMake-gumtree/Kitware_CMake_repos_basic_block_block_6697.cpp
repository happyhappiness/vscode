f(SSL_SET_OPTION(authtype) == CURL_TLSAUTH_SRP
         && SSL_SET_OPTION(username) != NULL
         && !SSL_CONN_CONFIG(verifypeer)
         && gnutls_cipher_get(session)) {
        /* no peer cert, but auth is ok if we have SRP user and cipher and no
           peer verify */
      }
      else {
#endif
        failf(data, "failed to get server cert");
        return CURLE_PEER_FAILED_VERIFICATION;
#ifdef USE_TLS_SRP
      }