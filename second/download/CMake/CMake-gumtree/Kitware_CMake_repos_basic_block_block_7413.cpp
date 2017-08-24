{
  curl_asn1Element e;
  const char *ccp;
  const char *p;
  bool matched;

  /* Check if first ASN.1 element at `beg' is the given OID.
     Return a pointer in the source after the OID if found, else NULL. */

  ccp = Curl_getASN1Element(&e, beg, end);
  if(!ccp || e.tag != CURL_ASN1_OBJECT_IDENTIFIER)
    return (const char *) NULL;

  p = OID2str(e.beg, e.end, FALSE);
  if(!p)
    return (const char *) NULL;

  matched = !strcmp(p, oid);
  free((char *) p);
  return matched? ccp: (const char *) NULL;
}