  if(curlx_strequal("active", str))
    return CURLFTPSSL_CCC_ACTIVE;
  warnf(config, "unrecognized ftp CCC method '%s', using default\n", str);
  return CURLFTPSSL_CCC_PASSIVE;
}

static ParameterError getparameter(char *flag, /* f or -long-flag */
                                   char *nextarg, /* NULL if unset */
                                   bool *usedarg, /* set to TRUE if the arg
                                                     has been used */
                                   struct Configurable *config)
{
