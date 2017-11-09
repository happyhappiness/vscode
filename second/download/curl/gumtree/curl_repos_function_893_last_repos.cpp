long delegation(struct OperationConfig *config, char *str)
{
  if(curl_strequal("none", str))
    return CURLGSSAPI_DELEGATION_NONE;
  if(curl_strequal("policy", str))
    return CURLGSSAPI_DELEGATION_POLICY_FLAG;
  if(curl_strequal("always", str))
    return CURLGSSAPI_DELEGATION_FLAG;

  warnf(config->global, "unrecognized delegation method '%s', using none\n",
        str);

  return CURLGSSAPI_DELEGATION_NONE;
}