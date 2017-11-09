ParameterError str2tls_max(long *val, const char *str)
{
   static struct s_tls_max {
    const char *tls_max_str;
    long tls_max;
  } const tls_max_array[] = {
    { "default", CURL_SSLVERSION_MAX_DEFAULT },
    { "1.0",     CURL_SSLVERSION_MAX_TLSv1_0 },
    { "1.1",     CURL_SSLVERSION_MAX_TLSv1_1 },
    { "1.2",     CURL_SSLVERSION_MAX_TLSv1_2 },
    { "1.3",     CURL_SSLVERSION_MAX_TLSv1_3 }
  };
  size_t i = 0;
  if(!str)
    return PARAM_REQUIRES_PARAMETER;
  for(i = 0; i < sizeof(tls_max_array)/sizeof(tls_max_array[0]); i++) {
    if(!strcmp(str, tls_max_array[i].tls_max_str)) {
      *val = tls_max_array[i].tls_max;
      return PARAM_OK;
    }
  }
  return PARAM_BAD_USE;
}