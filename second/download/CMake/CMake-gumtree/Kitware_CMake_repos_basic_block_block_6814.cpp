f(pubkey) {
      /* encode the public key as DER */
      SECItem *cert_der = PK11_DEREncodePublicKey(pubkey);
      if(cert_der) {
        /* compare the public key with the pinned public key */
        result = Curl_pin_peer_pubkey(data, pinnedpubkey, cert_der->data,
                                      cert_der->len);
        SECITEM_FreeItem(cert_der, PR_TRUE);
      }
      SECKEY_DestroyPublicKey(pubkey);
    }