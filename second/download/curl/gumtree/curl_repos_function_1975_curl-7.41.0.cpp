CURLcode Curl_sasl_parse_url_auth_option(struct SASL *sasl,
                                         const char *value, size_t len)
{
  CURLcode result = CURLE_OK;
  unsigned int mechbit;
  size_t mechlen;

  if(!len)
    return CURLE_URL_MALFORMAT;

    if(sasl->resetprefs) {
      sasl->resetprefs = FALSE;
      sasl->prefmech = SASL_AUTH_NONE;
    }

    if(strnequal(value, "*", len))
      sasl->prefmech = SASL_AUTH_DEFAULT;
    else if((mechbit = Curl_sasl_decode_mech(value, len, &mechlen)) &&
            mechlen == len)
      sasl->prefmech |= mechbit;
    else
      result = CURLE_URL_MALFORMAT;

  return result;
}