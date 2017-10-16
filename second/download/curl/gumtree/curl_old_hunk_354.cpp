
  return PARAM_OK;
}

static int ftpfilemethod(struct Configurable *config, const char *str)
{
  if(curlx_strequal("singlecwd", str))
    return CURLFTPMETHOD_SINGLECWD;
  if(curlx_strequal("nocwd", str))
    return CURLFTPMETHOD_NOCWD;
  if(curlx_strequal("multicwd", str))
    return CURLFTPMETHOD_MULTICWD;
  warnf(config, "unrecognized ftp file method '%s', using default\n", str);
  return CURLFTPMETHOD_MULTICWD;
}

static int ftpcccmethod(struct Configurable *config, const char *str)
{
  if(curlx_strequal("passive", str))
    return CURLFTPSSL_CCC_PASSIVE;
  if(curlx_strequal("active", str))
    return CURLFTPSSL_CCC_ACTIVE;
  warnf(config, "unrecognized ftp CCC method '%s', using default\n", str);
  return CURLFTPSSL_CCC_PASSIVE;
}


