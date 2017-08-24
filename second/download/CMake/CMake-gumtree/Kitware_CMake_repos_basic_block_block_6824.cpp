{
      failf(data, "NSS: PK11 slot not found: %s", pem_slotname);
      return SECFailure;
    }