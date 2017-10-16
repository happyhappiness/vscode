  char * cp2;
  CURLcode cc;
  unsigned long version;
  size_t i;
  size_t j;

  /* Prepare the certificate information for curl_easy_getinfo(). */

  /* Extract the certificate ASN.1 elements. */
  Curl_parseX509(&cert, beg, end);

  /* Subject. */
  ccp = Curl_DNtostr(&cert.subject);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  Curl_ssl_push_certinfo(data, certnum, "Subject", ccp);
  infof(data, "%2d Subject: %s\n", certnum, ccp);
  free((char *) ccp);

  /* Issuer. */
  ccp = Curl_DNtostr(&cert.issuer);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  Curl_ssl_push_certinfo(data, certnum, "Issuer", ccp);
  infof(data, "   Issuer: %s\n", ccp);
  free((char *) ccp);

  /* Version (always fits in less than 32 bits). */
  version = 0;
  for(ccp = cert.version.beg; ccp < cert.version.end; ccp++)
    version = (version << 8) | *(const unsigned char *) ccp;
  ccp = curl_maprintf("%lx", version);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  Curl_ssl_push_certinfo(data, certnum, "Version", ccp);
  free((char *) ccp);
  infof(data, "   Version: %lu (0x%lx)\n", version + 1, version);

  /* Serial number. */
  ccp = Curl_ASN1tostr(&cert.serialNumber, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  Curl_ssl_push_certinfo(data, certnum, "Serial Number", ccp);
  infof(data, "   Serial Number: %s\n", ccp);
  free((char *) ccp);

  /* Signature algorithm .*/
  ccp = dumpAlgo(&param, cert.signatureAlgorithm.beg,
                 cert.signatureAlgorithm.end);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  Curl_ssl_push_certinfo(data, certnum, "Signature Algorithm", ccp);
  infof(data, "   Signature Algorithm: %s\n", ccp);
  free((char *) ccp);

  /* Start Date. */
  ccp = Curl_ASN1tostr(&cert.notBefore, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  Curl_ssl_push_certinfo(data, certnum, "Start Date", ccp);
  infof(data, "   Start Date: %s\n", ccp);
  free((char *) ccp);

  /* Expire Date. */
  ccp = Curl_ASN1tostr(&cert.notAfter, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  Curl_ssl_push_certinfo(data, certnum, "Expire Date", ccp);
  infof(data, "   Expire Date: %s\n", ccp);
  free((char *) ccp);

  /* Public Key Algorithm. */
  ccp = dumpAlgo(&param, cert.subjectPublicKeyAlgorithm.beg,
                 cert.subjectPublicKeyAlgorithm.end);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  Curl_ssl_push_certinfo(data, certnum, "Public Key Algorithm", ccp);
  infof(data, "   Public Key Algorithm: %s\n", ccp);
  do_pubkey(data, certnum, ccp, &param, &cert.subjectPublicKey);
  free((char *) ccp);

/* TODO: extensions. */

  /* Signature. */
  ccp = Curl_ASN1tostr(&cert.signature, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  Curl_ssl_push_certinfo(data, certnum, "Signature", ccp);
  infof(data, "   Signature: %s\n", ccp);
  free((char *) ccp);

  /* Generate PEM certificate. */
  cc = Curl_base64_encode(data, cert.certificate.beg,
                          cert.certificate.end - cert.certificate.beg,
                          &cp1, &cl1);
  if(cc != CURLE_OK)
    return cc;
  /* Compute the number of charaters in final certificate string. Format is:
     -----BEGIN CERTIFICATE-----\n
     <max 64 base64 characters>\n
     .
     .
     .
     -----END CERTIFICATE-----\n
