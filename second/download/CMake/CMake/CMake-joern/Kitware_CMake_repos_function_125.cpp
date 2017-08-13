CURLcode Curl_extract_certinfo(struct connectdata *conn,
                               int certnum,
                               const char *beg,
                               const char *end)
{
  curl_X509certificate cert;
  struct Curl_easy *data = conn->data;
  curl_asn1Element param;
  const char *ccp;
  char *cp1;
  size_t cl1;
  char *cp2;
  CURLcode result;
  unsigned long version;
  size_t i;
  size_t j;

  if(!data->set.ssl.certinfo)
    if(certnum)
      return CURLE_OK;

  /* Prepare the certificate information for curl_easy_getinfo(). */

  /* Extract the certificate ASN.1 elements. */
  if(Curl_parseX509(&cert, beg, end))
    return CURLE_OUT_OF_MEMORY;

  /* Subject. */
  ccp = Curl_DNtostr(&cert.subject);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Subject", ccp);
  if(!certnum)
    infof(data, "%2d Subject: %s\n", certnum, ccp);
  free((char *) ccp);

  /* Issuer. */
  ccp = Curl_DNtostr(&cert.issuer);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Issuer", ccp);
  if(!certnum)
    infof(data, "   Issuer: %s\n", ccp);
  free((char *) ccp);

  /* Version (always fits in less than 32 bits). */
  version = 0;
  for(ccp = cert.version.beg; ccp < cert.version.end; ccp++)
    version = (version << 8) | *(const unsigned char *) ccp;
  if(data->set.ssl.certinfo) {
    ccp = curl_maprintf("%lx", version);
    if(!ccp)
      return CURLE_OUT_OF_MEMORY;
    Curl_ssl_push_certinfo(data, certnum, "Version", ccp);
    free((char *) ccp);
  }
  if(!certnum)
    infof(data, "   Version: %lu (0x%lx)\n", version + 1, version);

  /* Serial number. */
  ccp = Curl_ASN1tostr(&cert.serialNumber, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Serial Number", ccp);
  if(!certnum)
    infof(data, "   Serial Number: %s\n", ccp);
  free((char *) ccp);

  /* Signature algorithm .*/
  ccp = dumpAlgo(&param, cert.signatureAlgorithm.beg,
                 cert.signatureAlgorithm.end);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Signature Algorithm", ccp);
  if(!certnum)
    infof(data, "   Signature Algorithm: %s\n", ccp);
  free((char *) ccp);

  /* Start Date. */
  ccp = Curl_ASN1tostr(&cert.notBefore, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Start Date", ccp);
  if(!certnum)
    infof(data, "   Start Date: %s\n", ccp);
  free((char *) ccp);

  /* Expire Date. */
  ccp = Curl_ASN1tostr(&cert.notAfter, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Expire Date", ccp);
  if(!certnum)
    infof(data, "   Expire Date: %s\n", ccp);
  free((char *) ccp);

  /* Public Key Algorithm. */
  ccp = dumpAlgo(&param, cert.subjectPublicKeyAlgorithm.beg,
                 cert.subjectPublicKeyAlgorithm.end);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Public Key Algorithm", ccp);
  if(!certnum)
    infof(data, "   Public Key Algorithm: %s\n", ccp);
  do_pubkey(data, certnum, ccp, &param, &cert.subjectPublicKey);
  free((char *) ccp);

/* TODO: extensions. */

  /* Signature. */
  ccp = Curl_ASN1tostr(&cert.signature, 0);
  if(!ccp)
    return CURLE_OUT_OF_MEMORY;
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Signature", ccp);
  if(!certnum)
    infof(data, "   Signature: %s\n", ccp);
  free((char *) ccp);

  /* Generate PEM certificate. */
  result = Curl_base64_encode(data, cert.certificate.beg,
                              cert.certificate.end - cert.certificate.beg,
                              &cp1, &cl1);
  if(result)
    return result;
  /* Compute the number of characters in final certificate string. Format is:
     -----BEGIN CERTIFICATE-----\n
     <max 64 base64 characters>\n
     .
     .
     .
     -----END CERTIFICATE-----\n
   */
  i = 28 + cl1 + (cl1 + 64 - 1) / 64 + 26;
  cp2 = malloc(i + 1);
  if(!cp2) {
    free(cp1);
    return CURLE_OUT_OF_MEMORY;
  }
  /* Build the certificate string. */
  i = copySubstring(cp2, "-----BEGIN CERTIFICATE-----");
  for(j = 0; j < cl1; j += 64)
    i += copySubstring(cp2 + i, cp1 + j);
  i += copySubstring(cp2 + i, "-----END CERTIFICATE-----");
  cp2[i] = '\0';
  free(cp1);
  if(data->set.ssl.certinfo)
    Curl_ssl_push_certinfo(data, certnum, "Cert", cp2);
  if(!certnum)
    infof(data, "%s\n", cp2);
  free(cp2);
  return CURLE_OK;
}