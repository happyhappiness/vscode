int check_protocol(const char *str)
{
  const char * const *pp;
  const curl_version_info_data *curlinfo = curl_version_info(CURLVERSION_NOW);
  if(!str)
    return PARAM_REQUIRES_PARAMETER;
  for(pp = curlinfo->protocols; *pp; pp++) {
    if(curl_strequal(*pp, str))
      return PARAM_OK;
  }
  return PARAM_LIBCURL_UNSUPPORTED_PROTOCOL;
}