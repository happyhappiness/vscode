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