{
    /* There was no lowercase variable, try the uppercase version: */
    Curl_strntoupper(proxy_env, proxy_env, sizeof(proxy_env));
    prox=curl_getenv(proxy_env);
  }