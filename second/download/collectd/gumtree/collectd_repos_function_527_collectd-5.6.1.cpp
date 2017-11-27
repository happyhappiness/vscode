static int ascent_config (const char *key, const char *value) /* {{{ */
{
  if (strcasecmp (key, "URL") == 0)
    return (config_set (&url, value));
  else if (strcasecmp (key, "User") == 0)
    return (config_set (&user, value));
  else if (strcasecmp (key, "Password") == 0)
    return (config_set (&pass, value));
  else if (strcasecmp (key, "VerifyPeer") == 0)
    return (config_set (&verify_peer, value));
  else if (strcasecmp (key, "VerifyHost") == 0)
    return (config_set (&verify_host, value));
  else if (strcasecmp (key, "CACert") == 0)
    return (config_set (&cacert, value));
  else if (strcasecmp (key, "Timeout") == 0)
    return (config_set (&timeout, value));
  else
    return (-1);
}