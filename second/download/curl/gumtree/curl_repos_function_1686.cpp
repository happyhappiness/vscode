static const char * dumpAlgo(curl_asn1Element * param,
                             const char * beg, const char * end)
{
  curl_asn1Element oid;

  /* Get algorithm parameters and return algorithm name. */

  beg = Curl_getASN1Element(&oid, beg, end);
  param->header = NULL;
  param->tag = 0;
  param->beg = param->end = end;
  if(beg < end)
    Curl_getASN1Element(param, beg, end);
  return OID2str(oid.beg, oid.end, TRUE);
}