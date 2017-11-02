static long parse_auth_name(const char *arg)
{
  if (!arg)
    return CURLAUTH_NONE;
  if (strequal(arg, "basic"))
    return CURLAUTH_BASIC;
  if (strequal(arg, "digest"))
    return CURLAUTH_DIGEST;
  if (strequal(arg, "ntlm"))
    return CURLAUTH_NTLM;
  return CURLAUTH_NONE;
}