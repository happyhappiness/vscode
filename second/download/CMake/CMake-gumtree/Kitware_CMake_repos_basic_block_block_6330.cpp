{
    /* Generate our SPN */
    krb5->spn = Curl_auth_build_spn(service, host, NULL);
    if(!krb5->spn)
      return CURLE_OUT_OF_MEMORY;
  }