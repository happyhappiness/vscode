int ftpfilemethod(struct OperationConfig *config, const char *str)
{
  if(curlx_raw_equal("singlecwd", str))
    return CURLFTPMETHOD_SINGLECWD;
  if(curlx_raw_equal("nocwd", str))
    return CURLFTPMETHOD_NOCWD;
  if(curlx_raw_equal("multicwd", str))
    return CURLFTPMETHOD_MULTICWD;
  warnf(config, "unrecognized ftp file method '%s', using default\n", str);
  return CURLFTPMETHOD_MULTICWD;
}