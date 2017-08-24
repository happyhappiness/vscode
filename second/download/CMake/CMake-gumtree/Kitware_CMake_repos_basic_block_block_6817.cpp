{
    failf(data, "NSS: refusing previously loaded certificate from file: %s",
          nickname);
    return SECFailure;
  }