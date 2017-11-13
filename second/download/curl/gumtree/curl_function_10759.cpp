int ftpcccmethod(struct OperationConfig *config, const char *str)
{
  if(curlx_raw_equal("passive", str))
    return CURLFTPSSL_CCC_PASSIVE;
  if(curlx_raw_equal("active", str))
    return CURLFTPSSL_CCC_ACTIVE;
  warnf(config, "unrecognized ftp CCC method '%s', using default\n", str);
  return CURLFTPSSL_CCC_PASSIVE;
}