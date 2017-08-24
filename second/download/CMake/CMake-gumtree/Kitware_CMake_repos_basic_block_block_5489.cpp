{
    const char *key = ptr;
    const char *value;

    while(*ptr && *ptr != '=')
      ptr++;

    value = ptr + 1;

    while(*ptr && *ptr != ';')
      ptr++;

    if(strncasecompare(key, "AUTH=", 5))
      result = Curl_sasl_parse_url_auth_option(&smtpc->sasl,
                                               value, ptr - value);
    else
      result = CURLE_URL_MALFORMAT;

    if(*ptr == ';')
      ptr++;
  }