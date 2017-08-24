{
    failf(data, "NSS: private key not found for certificate: %s", nickname);
    return SECFailure;
  }