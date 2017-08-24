f(data->set.str[STRING_SSL_PINNEDPUBLICKEY_ORIG]) {
      CURLcode result = pkp_pin_peer_pubkey(data, connssl->ssl_ctx,
                            data->set.str[STRING_SSL_PINNEDPUBLICKEY_ORIG]);
      if(result) {
        failf(data, "SSL: public key does not match pinned public key!");
        return result;
      }
    }