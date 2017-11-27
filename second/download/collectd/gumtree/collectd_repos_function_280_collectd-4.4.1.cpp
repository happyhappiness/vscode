static int ascent_config (const char *key, const char *value) /* {{{ */
{
  if (strcasecmp (key, "URL") == 0)
    return (config_set (&url, value));
  else if (strcasecmp (key, "User") == 0)
    return (config_set (&user, value));
  else if (strcasecmp (key, "Password") == 0)
    return (config_set (&pass, value));
  else if (strcasecmp (key, "CACert") == 0)
    return (config_set (&cacert, value));
  else
    return (-1);
}