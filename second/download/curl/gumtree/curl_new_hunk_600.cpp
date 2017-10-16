    break;
  }

  return 0;
}

static long delegation(struct Configurable *config,
                       char *str)
{
  if(curlx_raw_equal("none", str))
    return CURLGSSAPI_DELEGATION_NONE;
  if(curlx_raw_equal("policy", str))
    return CURLGSSAPI_DELEGATION_POLICY_FLAG;
  if(curlx_raw_equal("always", str))
    return CURLGSSAPI_DELEGATION_FLAG;
  warnf(config, "unrecognized delegation method '%s', using none\n", str);
  return CURLGSSAPI_DELEGATION_NONE;
}

static ParameterError getparameter(char *flag, /* f or -long-flag */
                                   char *nextarg, /* NULL if unset */
                                   bool *usedarg, /* set to TRUE if the arg
                                                     has been used */
                                   struct Configurable *config)
