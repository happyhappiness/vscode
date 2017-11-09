static long parse_auth_name(const char *arg)
{
  if(!arg)
    return CURLAUTH_NONE;
  if(curl_strequal(arg, "basic"))
    return CURLAUTH_BASIC;
  if(curl_strequal(arg, "digest"))
    return CURLAUTH_DIGEST;
  if(curl_strequal(arg, "ntlm"))
    return CURLAUTH_NTLM;
  return CURLAUTH_NONE;
}