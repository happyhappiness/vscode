  if(curlx_strequal("multicwd", str))
    return CURLFTPMETHOD_MULTICWD;
  warnf(config, "unrecognized ftp file method '%s', using default\n", str);
  return CURLFTPMETHOD_MULTICWD;
}

static ParameterError getparameter(char *flag, /* f or -long-flag */
                                   char *nextarg, /* NULL if unset */
                                   bool *usedarg, /* set to TRUE if the arg
                                                     has been used */
                                   struct Configurable *config)
{
