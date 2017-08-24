r(i = 0; i < num_implemented_ciphers; i++) {
    SSL_CipherPrefSet(model, implemented_ciphers[i], PR_FALSE);
  }