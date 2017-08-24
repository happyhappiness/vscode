{
    /* destruct wildcard structures if it is needed */
    struct WildcardData *wc = &data->wildcard;
    Curl_wildcard_dtor(wc);
  }