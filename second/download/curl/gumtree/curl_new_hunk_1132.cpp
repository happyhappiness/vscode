
  return PARAM_OK;
}

int ftpfilemethod(struct OperationConfig *config, const char *str)
{
  if(curl_strequal("singlecwd", str))
    return CURLFTPMETHOD_SINGLECWD;
  if(curl_strequal("nocwd", str))
    return CURLFTPMETHOD_NOCWD;
  if(curl_strequal("multicwd", str))
    return CURLFTPMETHOD_MULTICWD;

  warnf(config->global, "unrecognized ftp file method '%s', using default\n",
        str);

  return CURLFTPMETHOD_MULTICWD;
}

int ftpcccmethod(struct OperationConfig *config, const char *str)
{
  if(curl_strequal("passive", str))
    return CURLFTPSSL_CCC_PASSIVE;
  if(curl_strequal("active", str))
    return CURLFTPSSL_CCC_ACTIVE;

  warnf(config->global, "unrecognized ftp CCC method '%s', using default\n",
        str);

  return CURLFTPSSL_CCC_PASSIVE;
}

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
