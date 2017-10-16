
  return PARAM_OK;
}

static int ftpfilemethod(struct Configurable *config, const char *str)
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

static int ftpcccmethod(struct Configurable *config, const char *str)
{
  if(curlx_raw_equal("passive", str))
    return CURLFTPSSL_CCC_PASSIVE;
  if(curlx_raw_equal("active", str))
    return CURLFTPSSL_CCC_ACTIVE;
  warnf(config, "unrecognized ftp CCC method '%s', using default\n", str);
  return CURLFTPSSL_CCC_PASSIVE;
}


