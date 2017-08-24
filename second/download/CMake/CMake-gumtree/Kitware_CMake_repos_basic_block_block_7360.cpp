{
  curl_asn1Element elem;
  curl_asn1Element tbsCertificate;
  const char *ccp;
  static const char defaultVersion = 0;  /* v1. */

  /* ASN.1 parse an X509 certificate into structure subfields.
     Syntax is assumed to have already been checked by the SSL backend.
     See RFC 5280. */

  cert->certificate.header = NULL;
  cert->certificate.beg = beg;
  cert->certificate.end = end;

  /* Get the sequence content. */
  if(!Curl_getASN1Element(&elem, beg, end))
    return -1;  /* Invalid bounds/size. */
  beg = elem.beg;
  end = elem.end;

  /* Get tbsCertificate. */
  beg = Curl_getASN1Element(&tbsCertificate, beg, end);
  /* Skip the signatureAlgorithm. */
  beg = Curl_getASN1Element(&cert->signatureAlgorithm, beg, end);
  /* Get the signatureValue. */
  Curl_getASN1Element(&cert->signature, beg, end);

  /* Parse TBSCertificate. */
  beg = tbsCertificate.beg;
  end = tbsCertificate.end;
  /* Get optional version, get serialNumber. */
  cert->version.header = NULL;
  cert->version.beg = &defaultVersion;
  cert->version.end = &defaultVersion + sizeof defaultVersion;;
  beg = Curl_getASN1Element(&elem, beg, end);
  if(elem.tag == 0) {
    Curl_getASN1Element(&cert->version, elem.beg, elem.end);
    beg = Curl_getASN1Element(&elem, beg, end);
  }
  cert->serialNumber = elem;
  /* Get signature algorithm. */
  beg = Curl_getASN1Element(&cert->signatureAlgorithm, beg, end);
  /* Get issuer. */
  beg = Curl_getASN1Element(&cert->issuer, beg, end);
  /* Get notBefore and notAfter. */
  beg = Curl_getASN1Element(&elem, beg, end);
  ccp = Curl_getASN1Element(&cert->notBefore, elem.beg, elem.end);
  Curl_getASN1Element(&cert->notAfter, ccp, elem.end);
  /* Get subject. */
  beg = Curl_getASN1Element(&cert->subject, beg, end);
  /* Get subjectPublicKeyAlgorithm and subjectPublicKey. */
  beg = Curl_getASN1Element(&cert->subjectPublicKeyInfo, beg, end);
  ccp = Curl_getASN1Element(&cert->subjectPublicKeyAlgorithm,
                            cert->subjectPublicKeyInfo.beg,
                            cert->subjectPublicKeyInfo.end);
  Curl_getASN1Element(&cert->subjectPublicKey, ccp,
                      cert->subjectPublicKeyInfo.end);
  /* Get optional issuerUiqueID, subjectUniqueID and extensions. */
  cert->issuerUniqueID.tag = cert->subjectUniqueID.tag = 0;
  cert->extensions.tag = elem.tag = 0;
  cert->issuerUniqueID.header = cert->subjectUniqueID.header = NULL;
  cert->issuerUniqueID.beg = cert->issuerUniqueID.end = "";
  cert->subjectUniqueID.beg = cert->subjectUniqueID.end = "";
  cert->extensions.header = NULL;
  cert->extensions.beg = cert->extensions.end = "";
  if(beg < end)
    beg = Curl_getASN1Element(&elem, beg, end);
  if(elem.tag == 1) {
    cert->issuerUniqueID = elem;
    if(beg < end)
      beg = Curl_getASN1Element(&elem, beg, end);
  }
  if(elem.tag == 2) {
    cert->subjectUniqueID = elem;
    if(beg < end)
      beg = Curl_getASN1Element(&elem, beg, end);
  }
  if(elem.tag == 3)
    Curl_getASN1Element(&cert->extensions, elem.beg, elem.end);
  return 0;
}