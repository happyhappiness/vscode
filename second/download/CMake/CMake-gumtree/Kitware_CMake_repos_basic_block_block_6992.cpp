{
    int size;
    CURLcode result;
    x509_crt *p;
    unsigned char pubkey[PUB_DER_MAX_BYTES];
    const x509_crt *peercert;

    peercert = ssl_get_peer_cert(&connssl->ssl);

    if(!peercert || !peercert->raw.p || !peercert->raw.len) {
      failf(data, "Failed due to missing peer certificate");
      return CURLE_SSL_PINNEDPUBKEYNOTMATCH;
    }

    p = calloc(1, sizeof(*p));

    if(!p)
      return CURLE_OUT_OF_MEMORY;

    x509_crt_init(p);

    /* Make a copy of our const peercert because pk_write_pubkey_der
       needs a non-const key, for now.
       https://github.com/ARMmbed/mbedtls/issues/396 */
    if(x509_crt_parse_der(p, peercert->raw.p, peercert->raw.len)) {
      failf(data, "Failed copying peer certificate");
      x509_crt_free(p);
      free(p);
      return CURLE_SSL_PINNEDPUBKEYNOTMATCH;
    }

    size = pk_write_pubkey_der(&p->pk, pubkey, PUB_DER_MAX_BYTES);

    if(size <= 0) {
      failf(data, "Failed copying public key from peer certificate");
      x509_crt_free(p);
      free(p);
      return CURLE_SSL_PINNEDPUBKEYNOTMATCH;
    }

    /* pk_write_pubkey_der writes data at the end of the buffer. */
    result = Curl_pin_peer_pubkey(data,
                                  pinnedpubkey,
                                  &pubkey[PUB_DER_MAX_BYTES - size], size);
    if(result) {
      x509_crt_free(p);
      free(p);
      return result;
    }

    x509_crt_free(p);
    free(p);
  }