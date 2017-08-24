{
    /* we have been connected fine, we're not waiting for anything else. */
    connssl->connecting_state = ssl_connect_3;

#ifdef DARWIN_SSL_PINNEDPUBKEY
    if(data->set.str[STRING_SSL_PINNEDPUBLICKEY_ORIG]) {
      CURLcode result = pkp_pin_peer_pubkey(data, connssl->ssl_ctx,
                            data->set.str[STRING_SSL_PINNEDPUBLICKEY_ORIG]);
      if(result) {
        failf(data, "SSL: public key does not match pinned public key!");
        return result;
      }
    }
#endif /* DARWIN_SSL_PINNEDPUBKEY */

    /* Informational message */
    (void)SSLGetNegotiatedCipher(connssl->ssl_ctx, &cipher);
    (void)SSLGetNegotiatedProtocolVersion(connssl->ssl_ctx, &protocol);
    switch(protocol) {
      case kSSLProtocol2:
        infof(data, "SSL 2.0 connection using %s\n",
              SSLCipherNameForNumber(cipher));
        break;
      case kSSLProtocol3:
        infof(data, "SSL 3.0 connection using %s\n",
              SSLCipherNameForNumber(cipher));
        break;
      case kTLSProtocol1:
        infof(data, "TLS 1.0 connection using %s\n",
              TLSCipherNameForNumber(cipher));
        break;
#if CURL_BUILD_MAC_10_8 || CURL_BUILD_IOS
      case kTLSProtocol11:
        infof(data, "TLS 1.1 connection using %s\n",
              TLSCipherNameForNumber(cipher));
        break;
      case kTLSProtocol12:
        infof(data, "TLS 1.2 connection using %s\n",
              TLSCipherNameForNumber(cipher));
        break;
#endif
      default:
        infof(data, "Unknown protocol connection\n");
        break;
    }

    return CURLE_OK;
  }