f(!nego->spn) {
    /* Generate our SPN */
    nego->spn = Curl_auth_build_spn(service, host, NULL);
    if(!nego->spn)
      return CURLE_OUT_OF_MEMORY;
  }