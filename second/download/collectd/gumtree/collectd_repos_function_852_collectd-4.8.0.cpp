static int config (const char *key, const char *value)
{
  if (strcasecmp (key, "url") == 0)
    return (config_set (&url, value));
  else if (strcasecmp (key, "user") == 0)
    return (config_set (&user, value));
  else if (strcasecmp (key, "password") == 0)
    return (config_set (&pass, value));
  else if (strcasecmp (key, "verifypeer") == 0)
    return (config_set (&verify_peer, value));
  else if (strcasecmp (key, "verifyhost") == 0)
    return (config_set (&verify_host, value));
  else if (strcasecmp (key, "cacert") == 0)
    return (config_set (&cacert, value));
  else
    return (-1);
}