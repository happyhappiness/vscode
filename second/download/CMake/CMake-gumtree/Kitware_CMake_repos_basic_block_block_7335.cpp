{
  case CURL_ASN1_BOOLEAN:
    return bool2str(elem->beg, elem->end);
  case CURL_ASN1_INTEGER:
  case CURL_ASN1_ENUMERATED:
    return int2str(elem->beg, elem->end);
  case CURL_ASN1_BIT_STRING:
    return bit2str(elem->beg, elem->end);
  case CURL_ASN1_OCTET_STRING:
    return octet2str(elem->beg, elem->end);
  case CURL_ASN1_NULL:
    return strdup("");
  case CURL_ASN1_OBJECT_IDENTIFIER:
    return OID2str(elem->beg, elem->end, TRUE);
  case CURL_ASN1_UTC_TIME:
    return UTime2str(elem->beg, elem->end);
  case CURL_ASN1_GENERALIZED_TIME:
    return GTime2str(elem->beg, elem->end);
  case CURL_ASN1_UTF8_STRING:
  case CURL_ASN1_NUMERIC_STRING:
  case CURL_ASN1_PRINTABLE_STRING:
  case CURL_ASN1_TELETEX_STRING:
  case CURL_ASN1_IA5_STRING:
  case CURL_ASN1_VISIBLE_STRING:
  case CURL_ASN1_UNIVERSAL_STRING:
  case CURL_ASN1_BMP_STRING:
    return string2str(type, elem->beg, elem->end);
  }